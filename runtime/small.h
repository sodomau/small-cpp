#pragma once

// Small C++ public API. Deliberately independent of Qt.
#include <chrono>
#include <cstddef>
#include <initializer_list>
#include <fstream>
#include <limits>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace Small
{

// Prepares the Small runtime when you write the real C++ main() yourself.
// small_main() programs are initialized automatically by Small's hidden entry point.
void initialize_small(int argc = 0, char** argv = nullptr);

// Finishes the Small runtime. Call this before returning from your own main().
// small_main() programs call it automatically through Small's hidden entry point.
void shutdown_small();


class String
{
public:
    String() = default;
    String(const char* text)
    {
        if (!text) throw std::invalid_argument("String cannot be made from a null pointer.");
        data_ = text;
        CheckLength(data_.size());
    }

    // Inbound C++ interoperability only; no implicit conversion back to std::string.
    String(const std::string& text) : data_(text)
    {
        CheckLength(data_.size());
    }

    // Interoperability overload; also preserves embedded zero bytes.
    String(const char* text, int length)
    {
        if (length < 0 || (!text && length != 0))
            throw std::invalid_argument("Invalid String data or length.");
        if (length != 0) data_.assign(text, static_cast<std::size_t>(length));
    }

    int length() const { return static_cast<int>(data_.size()); }
    const char* c_str() const { return data_.c_str(); }

    char& operator[](int index) { CheckIndex(index); return data_[index]; }
    const char& operator[](int index) const { CheckIndex(index); return data_[index]; }

    String substring(int start) const
    {
        CheckStart(start);
        return substring(start, length() - start);
    }

    String substring(int start, int length) const
    {
        CheckStart(start);
        // Subtraction avoids overflowing start + length.
        if (length < 0 || length > this->length() - start)
            throw std::out_of_range("substring extends beyond the String.");
        return String(data_.data() + start, length);
    }

    String& operator+=(const String& other)
    {
        if (other.length() > std::numeric_limits<int>::max() - length())
            throw std::length_error("String is too long.");
        data_ += other.data_;
        return *this;
    }

    bool operator==(const String& other) const { return data_ == other.data_; }
    bool operator!=(const String& other) const { return data_ != other.data_; }
    bool operator< (const String& other) const { return data_ <  other.data_; }
    bool operator<=(const String& other) const { return data_ <= other.data_; }
    bool operator> (const String& other) const { return data_ >  other.data_; }
    bool operator>=(const String& other) const { return data_ >= other.data_; }

private:
    std::string data_;

    static void CheckLength(std::size_t length)
    {
        if (length > static_cast<std::size_t>(std::numeric_limits<int>::max()))
            throw std::length_error("String is too long.");
    }
    void CheckStart(int start) const
    {
        if (start < 0 || start > length())
            throw std::out_of_range("substring start index is out of range.");
    }
    void CheckIndex(int index) const
    {
        if (index < 0 || index >= length())
            throw std::out_of_range("String index " + std::to_string(index) +
                " is out of range. length: " + std::to_string(length()) + ".");
    }
};

inline String operator+(String left, const String& right)
{
    left += right;
    return left;
}
inline std::ostream& operator<<(std::ostream& out, const String& text)
{
    return out.write(text.c_str(), text.length());
}

// Allow a literal on the left, too. No friend functions are needed.
inline bool operator==(const char* left, const String& right) { return String(left) == right; }
inline bool operator!=(const char* left, const String& right) { return String(left) != right; }
inline bool operator< (const char* left, const String& right) { return String(left) <  right; }
inline bool operator<=(const char* left, const String& right) { return String(left) <= right; }
inline bool operator> (const char* left, const String& right) { return String(left) >  right; }
inline bool operator>=(const char* left, const String& right) { return String(left) >= right; }

template<typename T>
class Array
{
public:
    Array() = default;
    explicit Array(int length)
    {
        if (length < 0) throw std::invalid_argument("Array length cannot be negative.");
        data_.resize(static_cast<std::size_t>(length));
    }
    Array(std::initializer_list<T> values)
    {
        if (values.size() > static_cast<std::size_t>(std::numeric_limits<int>::max()))
            throw std::length_error("Array is too long.");
        data_.reserve(values.size());
        for (const T& value : values) data_.push_back(Element{value});
    }

    int length() const { return static_cast<int>(data_.size()); }
    T& operator[](int index) { CheckIndex(index); return data_[index].value; }
    const T& operator[](int index) const { CheckIndex(index); return data_[index].value; }

    // Compiler-generated copy/assignment copy every element, including when
    // the two Arrays have different lengths. No Resize/Append operations.
private:
    // Avoid std::vector<bool>'s proxy references: Array<bool> has real bools.
    struct Element { T value{}; };
    std::vector<Element> data_;

    void CheckIndex(int index) const
    {
        if (index < 0 || index >= length())
            throw std::out_of_range("Array index " + std::to_string(index) +
                " is out of range. length: " + std::to_string(length()) + ".");
    }
};

namespace small_detail
{
    std::ostream& Console();
}

template<typename... Args>
void write(const Args&... args)
{
    std::ostream& out = small_detail::Console();
    if constexpr (sizeof...(Args) > 0) (out << ... << args);
    out.flush();
}

template<typename... Args>
void print(const Args&... args)
{
    std::ostream& out = small_detail::Console();
    if constexpr (sizeof...(Args) > 0) (out << ... << args);
    out.put('\n');
    out.flush();
}

template<typename... Args>
String format(const Args&... args)
{
    std::ostringstream out;
    if constexpr (sizeof...(Args) > 0) (out << ... << args);
    const std::string text = out.str();
    if (text.size() > static_cast<std::size_t>(std::numeric_limits<int>::max()))
        throw std::length_error("String is too long.");
    return String(text.data(), static_cast<int>(text.size()));
}

String input();
String input(const String& prompt);
int input_int();
int input_int(const String& prompt);
double input_real();
double input_real(const String& prompt);


enum class FileMode
{
    Read,
    Write,
    Append,
    ReadBinary,
    WriteBinary,
    AppendBinary
};

class File
{
public:
    File() = default;
    ~File() { close(); }

    File(const File&) = delete;
    File& operator=(const File&) = delete;

    void open(const String& file_name, FileMode mode = FileMode::Read)
    {
        close();

        std::ios::openmode flags = std::ios::in;
        if (mode == FileMode::Write)
            flags = std::ios::out | std::ios::trunc;
        else if (mode == FileMode::Append)
            flags = std::ios::out | std::ios::app;
        else if (mode == FileMode::ReadBinary)
            flags = std::ios::in | std::ios::binary;
        else if (mode == FileMode::WriteBinary)
            flags = std::ios::out | std::ios::trunc | std::ios::binary;
        else if (mode == FileMode::AppendBinary)
            flags = std::ios::out | std::ios::app | std::ios::binary;

        stream_.open(file_name.c_str(), flags);
        if (!stream_.is_open())
            throw std::runtime_error("Could not open file: " + std::string(file_name.c_str()) + ".");

        mode_ = mode;
    }

    void close()
    {
        if (stream_.is_open()) stream_.close();
    }

    bool is_open() const { return stream_.is_open(); }

    bool end()
    {
        CheckReadable();
        return stream_.peek() == std::char_traits<char>::eof();
    }

    String input()
    {
        CheckReadable();
        std::string line;
        if (!std::getline(stream_, line))
        {
            if (stream_.eof()) return String();
            throw std::runtime_error("Could not read from file.");
        }
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.size() > static_cast<std::size_t>(std::numeric_limits<int>::max()))
            throw std::length_error("input is too long.");
        return String(line.data(), static_cast<int>(line.size()));
    }

    int input_int()
    {
        return ReadNumber<int>("integer");
    }

    double input_real()
    {
        return ReadNumber<double>("number");
    }

    template<typename... Args>
    void write(const Args&... args)
    {
        CheckWritable();
        if constexpr (sizeof...(Args) > 0) (stream_ << ... << args);
        if (!stream_) throw std::runtime_error("Could not write to file.");
        stream_.flush();
    }

    template<typename... Args>
    void print(const Args&... args)
    {
        CheckWritable();
        if constexpr (sizeof...(Args) > 0) (stream_ << ... << args);
        stream_.put('\n');
        if (!stream_) throw std::runtime_error("Could not write to file.");
        stream_.flush();
    }

    int read_int()
    {
        CheckBinaryReadable();
        int value = 0;
        stream_.read(reinterpret_cast<char*>(&value), sizeof(value));
        if (!stream_) throw std::runtime_error("Could not read an int from file.");
        return value;
    }

    double read_real()
    {
        CheckBinaryReadable();
        double value = 0.0;
        stream_.read(reinterpret_cast<char*>(&value), sizeof(value));
        if (!stream_) throw std::runtime_error("Could not read a real from file.");
        return value;
    }

    void write_int(int value)
    {
        CheckBinaryWritable();
        stream_.write(reinterpret_cast<const char*>(&value), sizeof(value));
        if (!stream_) throw std::runtime_error("Could not write an int to file.");
    }

    void write_real(double value)
    {
        CheckBinaryWritable();
        stream_.write(reinterpret_cast<const char*>(&value), sizeof(value));
        if (!stream_) throw std::runtime_error("Could not write a real to file.");
    }

private:
    std::fstream stream_;
    FileMode mode_ = FileMode::Read;

    void CheckReadable() const
    {
        if (!stream_.is_open())
            throw std::runtime_error("File is not open.");
        if (mode_ != FileMode::Read)
            throw std::runtime_error("File is not open for text reading.");
    }

    void CheckWritable() const
    {
        if (!stream_.is_open())
            throw std::runtime_error("File is not open.");
        if (mode_ != FileMode::Write && mode_ != FileMode::Append)
            throw std::runtime_error("File is not open for text writing.");
    }

    void CheckBinaryReadable() const
    {
        if (!stream_.is_open())
            throw std::runtime_error("File is not open.");
        if (mode_ != FileMode::ReadBinary)
            throw std::runtime_error("File is not open for binary reading.");
    }

    void CheckBinaryWritable() const
    {
        if (!stream_.is_open())
            throw std::runtime_error("File is not open.");
        if (mode_ != FileMode::WriteBinary && mode_ != FileMode::AppendBinary)
            throw std::runtime_error("File is not open for binary writing.");
    }

    template<typename T>
    T ReadNumber(const char* kind)
    {
        CheckReadable();
        T value{};
        if (!(stream_ >> value))
            throw std::runtime_error(std::string("Could not read an ") + kind + " from file.");
        stream_.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }
};

class Color
{
public:
    Color() = default;
    int red() const { return red_; }
    int green() const { return green_; }
    int blue() const { return blue_; }
    void set_rgb(int red, int green, int blue);
private:
    int red_ = 0, green_ = 0, blue_ = 0;
};

Color rgb(int red, int green, int blue);
extern const Color Black, White, Red, Green, Blue, Yellow, Cyan, Magenta, Gray;

enum class Key
{
    Left, Right, Up, Down, Space, Enter, Escape, Tab, Backspace, Delete
};

enum class MouseButton
{
    Left, Right, Middle
};

enum class Sound
{
    Click, Pop, Jump, Hit, Coin, Shoot, Explosion, Win, Lose
};

class StopWatch
{
public:
    StopWatch() : start_(std::chrono::steady_clock::now()) {}
    void reset() { start_ = std::chrono::steady_clock::now(); }
    double elapsed() const
    {
        return std::chrono::duration<double>(std::chrono::steady_clock::now() - start_).count();
    }
private:
    std::chrono::steady_clock::time_point start_;
};

// random_int includes both endpoints. random_real includes min and excludes max.
int random_int(int min, int max);
double random_real(double min, double max);

void sleep(double seconds);

// Calls a function repeatedly at the requested interval.
// The callback must take no parameters and return void.
class Timer
{
public:
    Timer() = default;
    ~Timer();
    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;

    void start(double interval, void (*callback)());
    void stop();
    bool is_running() const;

private:
    struct Impl;
    Impl* impl_ = nullptr;
};

class Window;
namespace small_detail { struct WindowAccess; }

class Window
{
public:
    Window();
    ~Window();
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    void open(int width, int height);
    void set_title(const String& title);

    template<typename First, typename... Rest>
    void set_title(const First& first, const Rest&... rest)
    {
        set_title(Small::format(first, rest...));
    }

    String title() const;
    void close();
    bool is_open();
    int width() const;
    int height() const;

    void clear(Color color);
    void set_pixel(int x, int y, Color color);
    void draw_line(double x1, double y1, double x2, double y2, Color color);
    void draw_rectangle(double x, double y, double width, double height, Color color);
    void fill_rectangle(double x, double y, double width, double height, Color color);
    void draw_circle(double x, double y, double radius, Color color);
    void fill_circle(double x, double y, double radius, Color color);
    void draw_text(double x, double y, const String& text);
    void draw_text(double x, double y, const String& text, Color color, int size);
    void show();

    bool key_down(Key key) const;
    bool key_pressed(Key key) const;
    bool key_released(Key key) const;
    bool key_down(char key) const;
    bool key_pressed(char key) const;
    bool key_released(char key) const;

    int mouse_x() const;
    int mouse_y() const;
    bool mouse_down(MouseButton button) const;
    bool mouse_pressed(MouseButton button) const;
    bool mouse_released(MouseButton button) const;

private:
    friend struct small_detail::WindowAccess;
    struct Impl;
    Impl* impl_ = nullptr;   // Owned; allocated only by open().
    String title_ = "Small C++";
    void CheckOpen() const;
};

void play_sound(Sound sound);
void play_sound_and_wait(Sound sound);
void beep(double frequency, double seconds);
void beep_and_wait(double frequency, double seconds);

} // namespace Small

#ifdef SMALL_BEGINNER_MODE
using namespace Small;
#endif

void small_main();

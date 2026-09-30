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
// SmallMain() programs are initialized automatically by Small's hidden entry point.
void InitializeSmall(int argc = 0, char** argv = nullptr);

// Finishes the Small runtime. Call this before returning from your own main().
// SmallMain() programs call it automatically through Small's hidden entry point.
void ShutdownSmall();


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

    int Length() const { return static_cast<int>(data_.size()); }
    const char* c_str() const { return data_.c_str(); }

    char& operator[](int index) { CheckIndex(index); return data_[index]; }
    const char& operator[](int index) const { CheckIndex(index); return data_[index]; }

    String Substring(int start) const
    {
        CheckStart(start);
        return Substring(start, Length() - start);
    }

    String Substring(int start, int length) const
    {
        CheckStart(start);
        // Subtraction avoids overflowing start + length.
        if (length < 0 || length > Length() - start)
            throw std::out_of_range("Substring extends beyond the String.");
        return String(data_.data() + start, length);
    }

    String& operator+=(const String& other)
    {
        if (other.Length() > std::numeric_limits<int>::max() - Length())
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
        if (start < 0 || start > Length())
            throw std::out_of_range("Substring start index is out of range.");
    }
    void CheckIndex(int index) const
    {
        if (index < 0 || index >= Length())
            throw std::out_of_range("String index " + std::to_string(index) +
                " is out of range. Length: " + std::to_string(Length()) + ".");
    }
};

inline String operator+(String left, const String& right)
{
    left += right;
    return left;
}
inline std::ostream& operator<<(std::ostream& out, const String& text)
{
    return out.write(text.c_str(), text.Length());
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

    int Length() const { return static_cast<int>(data_.size()); }
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
        if (index < 0 || index >= Length())
            throw std::out_of_range("Array index " + std::to_string(index) +
                " is out of range. Length: " + std::to_string(Length()) + ".");
    }
};

namespace small_detail
{
    std::ostream& Console();
}

template<typename... Args>
void Write(const Args&... args)
{
    std::ostream& out = small_detail::Console();
    if constexpr (sizeof...(Args) > 0) (out << ... << args);
    out.flush();
}

template<typename... Args>
void Print(const Args&... args)
{
    std::ostream& out = small_detail::Console();
    if constexpr (sizeof...(Args) > 0) (out << ... << args);
    out.put('\n');
    out.flush();
}

template<typename... Args>
String Format(const Args&... args)
{
    std::ostringstream out;
    if constexpr (sizeof...(Args) > 0) (out << ... << args);
    const std::string text = out.str();
    if (text.size() > static_cast<std::size_t>(std::numeric_limits<int>::max()))
        throw std::length_error("String is too long.");
    return String(text.data(), static_cast<int>(text.size()));
}

String Input();
String Input(const String& prompt);
int InputInt();
int InputInt(const String& prompt);
double InputReal();
double InputReal(const String& prompt);


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
    ~File() { Close(); }

    File(const File&) = delete;
    File& operator=(const File&) = delete;

    void Open(const String& filename, FileMode mode = FileMode::Read)
    {
        Close();

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

        stream_.open(filename.c_str(), flags);
        if (!stream_.is_open())
            throw std::runtime_error("Could not open file: " + std::string(filename.c_str()) + ".");

        mode_ = mode;
    }

    void Close()
    {
        if (stream_.is_open()) stream_.close();
    }

    bool IsOpen() const { return stream_.is_open(); }

    bool End()
    {
        CheckReadable();
        return stream_.peek() == std::char_traits<char>::eof();
    }

    String Input()
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
            throw std::length_error("Input is too long.");
        return String(line.data(), static_cast<int>(line.size()));
    }

    int InputInt()
    {
        return ReadNumber<int>("integer");
    }

    double InputReal()
    {
        return ReadNumber<double>("number");
    }

    template<typename... Args>
    void Write(const Args&... args)
    {
        CheckWritable();
        if constexpr (sizeof...(Args) > 0) (stream_ << ... << args);
        if (!stream_) throw std::runtime_error("Could not write to file.");
        stream_.flush();
    }

    template<typename... Args>
    void Print(const Args&... args)
    {
        CheckWritable();
        if constexpr (sizeof...(Args) > 0) (stream_ << ... << args);
        stream_.put('\n');
        if (!stream_) throw std::runtime_error("Could not write to file.");
        stream_.flush();
    }

    int ReadInt()
    {
        CheckBinaryReadable();
        int value = 0;
        stream_.read(reinterpret_cast<char*>(&value), sizeof(value));
        if (!stream_) throw std::runtime_error("Could not read an int from file.");
        return value;
    }

    double ReadReal()
    {
        CheckBinaryReadable();
        double value = 0.0;
        stream_.read(reinterpret_cast<char*>(&value), sizeof(value));
        if (!stream_) throw std::runtime_error("Could not read a real from file.");
        return value;
    }

    void WriteInt(int value)
    {
        CheckBinaryWritable();
        stream_.write(reinterpret_cast<const char*>(&value), sizeof(value));
        if (!stream_) throw std::runtime_error("Could not write an int to file.");
    }

    void WriteReal(double value)
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
    int Red() const { return red_; }
    int Green() const { return green_; }
    int Blue() const { return blue_; }
    void SetRGB(int red, int green, int blue);
private:
    int red_ = 0, green_ = 0, blue_ = 0;
};

Color RGB(int red, int green, int blue);
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
    void Reset() { start_ = std::chrono::steady_clock::now(); }
    double Elapsed() const
    {
        return std::chrono::duration<double>(std::chrono::steady_clock::now() - start_).count();
    }
private:
    std::chrono::steady_clock::time_point start_;
};

// RandomInt includes both endpoints. RandomReal includes min and excludes max.
int RandomInt(int min, int max);
double RandomReal(double min, double max);

void Sleep(double seconds);

// Calls a function repeatedly at the requested interval.
// The callback must take no parameters and return void.
class Timer
{
public:
    Timer() = default;
    ~Timer();
    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;

    void Start(double interval, void (*callback)());
    void Stop();
    bool IsRunning() const;

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

    void Open(int width, int height);
    void SetTitle(const String& title);

    template<typename First, typename... Rest>
    void SetTitle(const First& first, const Rest&... rest)
    {
        SetTitle(Format(first, rest...));
    }

    String Title() const;
    void Close();
    bool IsOpen();
    int Width() const;
    int Height() const;

    void Clear(Color color);
    void SetPixel(int x, int y, Color color);
    void DrawLine(double x1, double y1, double x2, double y2, Color color);
    void DrawRectangle(double x, double y, double width, double height, Color color);
    void FillRectangle(double x, double y, double width, double height, Color color);
    void DrawCircle(double x, double y, double radius, Color color);
    void FillCircle(double x, double y, double radius, Color color);
    void DrawText(double x, double y, const String& text);
    void DrawText(double x, double y, const String& text, Color color, int size);
    void Show();

    bool KeyDown(Key key) const;
    bool KeyPressed(Key key) const;
    bool KeyReleased(Key key) const;
    bool KeyDown(char key) const;
    bool KeyPressed(char key) const;
    bool KeyReleased(char key) const;

    int MouseX() const;
    int MouseY() const;
    bool MouseDown(MouseButton button) const;
    bool MousePressed(MouseButton button) const;
    bool MouseReleased(MouseButton button) const;

private:
    friend struct small_detail::WindowAccess;
    struct Impl;
    Impl* impl_ = nullptr;   // Owned; allocated only by Open().
    String title_ = "Small C++";
    void CheckOpen() const;
};

void PlaySound(Sound sound);
void PlaySoundAndWait(Sound sound);
void Beep(double frequency, double seconds);
void BeepAndWait(double frequency, double seconds);

} // namespace Small

#ifdef SMALL_BEGINNER_MODE
using namespace Small;
#endif

void SmallMain();

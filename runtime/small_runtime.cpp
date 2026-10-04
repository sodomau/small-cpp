#include "small.h"
#include "small_internal.h"

#include <QApplication>
#include <QLoggingCategory>
#include <QCloseEvent>
#include <QCoreApplication>
#include <QEventLoop>
#include <QFocusEvent>
#include <QFontMetricsF>
#include <QImage>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QThread>
#include <QTimer>
#include <QWidget>

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <locale>
#include <sstream>
#include <cstdlib>
#include <memory>
#include <random>
#include <string>
#include <vector>

namespace Small
{
namespace
{
struct RuntimeState
{
    int argc = 0;
    std::vector<std::string> arguments;
    std::vector<char*> argv;
    std::unique_ptr<QApplication> app;
};

RuntimeState& Runtime()
{
    // Intentionally leaked so C++ static-destruction order never owns the
    // Small runtime lifetime. initialize_small/shutdown_small define it explicitly.
    static RuntimeState* state = new RuntimeState;
    return *state;
}

}

void initialize_small(int argc, char** argv)
{
    auto& state = Runtime();
    if (state.app) return; // Safe and simple if called twice.

    if (argc < 0)
        throw std::invalid_argument("initialize_small(): argc cannot be negative.");
    if (argc > 0 && !argv)
        throw std::invalid_argument("initialize_small(): argv cannot be null when argc is positive.");

    small_detail::InitializePlatform();

    QLoggingCategory::setFilterRules(
        "qt.multimedia.debug=false\n"
        "qt.multimedia.info=false\n"
        "qt.multimedia.ffmpeg.debug=false\n"
        "qt.multimedia.ffmpeg.info=false");

    state.arguments.clear();
    if (argc == 0)
    {
        state.arguments.emplace_back("SmallCpp");
    }
    else
    {
        state.arguments.reserve(static_cast<std::size_t>(argc));
        for (int i = 0; i < argc; ++i)
            state.arguments.emplace_back(argv[i] ? argv[i] : "");
    }

    state.argv.clear();
    state.argv.reserve(state.arguments.size() + 1);
    for (std::string& argument : state.arguments)
        state.argv.push_back(argument.data());
    state.argv.push_back(nullptr);
    state.argc = static_cast<int>(state.arguments.size());

    state.app = std::make_unique<QApplication>(state.argc, state.argv.data());
    QApplication::setQuitOnLastWindowClosed(false);

}

void shutdown_small()
{
    auto& state = Runtime();
    if (!state.app) return; // Safe if called twice or after partial setup.

    // All Qt-dependent Small subsystems must be destroyed while QApplication
    // and Qt's runtime are still unquestionably alive.
    small_detail::ShutdownAudio();

    // Destroy QApplication only after dependent Small/Qt objects are gone.
    state.app.reset();
}

namespace small_detail
{
std::ostream& Console() { return std::cout; }
}

namespace
{
void ProcessEvents()
{
    if (QCoreApplication::instance())
        QCoreApplication::processEvents(QEventLoop::AllEvents);
}

std::string ReadLine()
{
    std::string line;
    if (!std::getline(std::cin, line))
        throw std::runtime_error("input ended before a value was entered.");
    // Windows console/pipe input may end with CRLF.
    if (!line.empty() && line.back() == '\r') line.pop_back();
    return line;
}

template<typename T>
T ReadNumber(const char* retryMessage)
{
    for (;;)
    {
        std::istringstream in(ReadLine());
        in.imbue(std::locale::classic());
        T value{};
        if (in >> value)
        {
            in >> std::ws;
            if (in.eof() && std::isfinite(static_cast<double>(value))) return value;
        }
        write(retryMessage);
    }
}

QColor ToQt(Color color)
{
    return QColor(color.red(), color.green(), color.blue());
}

void CheckFinite(std::initializer_list<double> values)
{
    for (double value : values)
        if (!std::isfinite(value))
            throw std::invalid_argument("Drawing coordinates must be finite numbers.");
}

int SpecialIndex(Key key)
{
    const int index = static_cast<int>(key);
    if (index < 0 || index >= 10) throw std::invalid_argument("Unknown key.");
    return index;
}

int CharacterIndex(char key)
{
    unsigned char c = static_cast<unsigned char>(key);
    if (c >= 'a' && c <= 'z') c -= 'a' - 'A';
    return c;
}

int MapSpecial(int key)
{
    switch (key)
    {
    case Qt::Key_Left:      return SpecialIndex(Key::Left);
    case Qt::Key_Right:     return SpecialIndex(Key::Right);
    case Qt::Key_Up:        return SpecialIndex(Key::Up);
    case Qt::Key_Down:      return SpecialIndex(Key::Down);
    case Qt::Key_Space:     return SpecialIndex(Key::Space);
    case Qt::Key_Return:
    case Qt::Key_Enter:     return SpecialIndex(Key::Enter);
    case Qt::Key_Escape:    return SpecialIndex(Key::Escape);
    case Qt::Key_Tab:       return SpecialIndex(Key::Tab);
    case Qt::Key_Backspace: return SpecialIndex(Key::Backspace);
    case Qt::Key_Delete:    return SpecialIndex(Key::Delete);
    default:               return -1;
    }
}
}

String input()
{
    const std::string line = ReadLine();
    if (line.size() > static_cast<std::size_t>(std::numeric_limits<int>::max()))
        throw std::length_error("input is too long.");
    return String(line.data(), static_cast<int>(line.size()));
}
String input(const String& prompt) { write(prompt); return input(); }
int input_int() { return ReadNumber<int>("Please enter an integer: "); }
int input_int(const String& prompt) { write(prompt); return input_int(); }
double input_real() { return ReadNumber<double>("Please enter a number: "); }
double input_real(const String& prompt) { write(prompt); return input_real(); }

void Color::set_rgb(int red, int green, int blue)
{
    if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
        throw std::out_of_range("Color values must be between 0 and 255.");
    red_ = red;
    green_ = green;
    blue_ = blue;
}

Color rgb(int red, int green, int blue)
{
    Color result;
    result.set_rgb(red, green, blue);
    return result;
}

const Color Black   = rgb(0, 0, 0);
const Color White   = rgb(255, 255, 255);
const Color Red     = rgb(255, 0, 0);
const Color Green   = rgb(0, 255, 0);
const Color Blue    = rgb(0, 0, 255);
const Color Yellow  = rgb(255, 255, 0);
const Color Cyan    = rgb(0, 255, 255);
const Color Magenta = rgb(255, 0, 255);
const Color Gray    = rgb(128, 128, 128);

namespace
{
std::mt19937& RandomEngine()
{
    static thread_local std::mt19937 engine(std::random_device{}());
    return engine;
}
}

int random_int(int min, int max)
{
    if (min > max)
        throw std::invalid_argument("random_int minimum cannot be greater than maximum.");
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(RandomEngine());
}

double random_real(double min, double max)
{
    if (!std::isfinite(min) || !std::isfinite(max))
        throw std::invalid_argument("random_real bounds must be finite.");
    if (min > max)
        throw std::invalid_argument("random_real minimum cannot be greater than maximum.");
    if (min == max) return min;
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(RandomEngine());
}

void sleep(double seconds)
{
    if (!std::isfinite(seconds) || seconds < 0)
        throw std::invalid_argument("sleep duration must be a non-negative, finite number.");
    StopWatch timer;
    while (timer.elapsed() < seconds)
    {
        ProcessEvents();
        const double remaining = seconds - timer.elapsed();
        if (remaining > 0)
            QThread::usleep(static_cast<unsigned long>(std::max(1.0, std::min(remaining, 0.005) * 1.0e6)));
    }
}

struct Timer::Impl
{
    QTimer timer;
    void (*callback)() = nullptr;

    Impl()
    {
        QObject::connect(&timer, &QTimer::timeout, [&]
        {
            if (!callback) return;
            try
            {
                callback();
            }
            catch (const std::exception& e)
            {
                timer.stop();
                std::cerr << "Timer callback error: " << e.what() << '\n';
            }
            catch (...)
            {
                timer.stop();
                std::cerr << "Timer callback error.\n";
            }
        });
    }
};

Timer::~Timer() { delete impl_; }

void Timer::start(double interval, void (*callback)())
{
    if (!std::isfinite(interval) || interval <= 0)
        throw std::invalid_argument("Timer interval must be a positive, finite number.");
    if (!callback)
        throw std::invalid_argument("Timer callback cannot be empty.");
    if (!impl_) impl_ = new Impl;
    impl_->callback = callback;
    impl_->timer.start(std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::duration<double>(interval)));
}

void Timer::stop()
{
    if (impl_) impl_->timer.stop();
}

bool Timer::is_running() const
{
    return impl_ && impl_->timer.isActive();
}

struct Window::Impl : QWidget
{
    QImage back;
    QImage front;
    bool closed = true;
    std::array<bool, 10> down{}, pressed{}, released{};
    std::array<bool, 256> charDown{}, charPressed{}, charReleased{};
    std::array<bool, 3> mouseDown{}, mousePressed{}, mouseReleased{};
    int mouseX = 0, mouseY = 0;

    Impl() { setFocusPolicy(Qt::StrongFocus); setMouseTracking(true); }

    void ResetKeys()
    {
        down.fill(false); pressed.fill(false); released.fill(false);
        charDown.fill(false); charPressed.fill(false); charReleased.fill(false);
        mouseDown.fill(false); mousePressed.fill(false); mouseReleased.fill(false);
    }
    void BeginNextFrame()
    {
        pressed.fill(false); released.fill(false);
        charPressed.fill(false); charReleased.fill(false);
        mousePressed.fill(false); mouseReleased.fill(false);
    }
    void ReleaseKeys()
    {
        for (std::size_t i = 0; i < down.size(); ++i)
        {
            released[i] = released[i] || down[i];
            down[i] = false;
        }
        for (std::size_t i = 0; i < charDown.size(); ++i)
        {
            charReleased[i] = charReleased[i] || charDown[i];
            charDown[i] = false;
        }
        for (std::size_t i = 0; i < mouseDown.size(); ++i)
        {
            mouseReleased[i] = mouseReleased[i] || mouseDown[i];
            mouseDown[i] = false;
        }
    }

    void paintEvent(QPaintEvent*) override
    {
        // Never display a partially drawn back buffer during OS repaint.
        QPainter painter(this);
        if (!front.isNull()) painter.drawImage(0, 0, front);
    }
    void closeEvent(QCloseEvent* event) override
    {
        closed = true;
        ReleaseKeys();
        event->accept();
    }
    void focusOutEvent(QFocusEvent* event) override
    {
        ReleaseKeys();
        QWidget::focusOutEvent(event);
    }
    bool event(QEvent* event) override
    {
        // QWidget normally consumes Tab for focus traversal.
        if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
        {
            auto* keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Tab)
            {
                HandleKey(keyEvent, event->type() == QEvent::KeyPress);
                return true;
            }
        }
        return QWidget::event(event);
    }
    void keyPressEvent(QKeyEvent* event) override { HandleKey(event, true); }
    void keyReleaseEvent(QKeyEvent* event) override { HandleKey(event, false); }
    void mouseMoveEvent(QMouseEvent* event) override
    {
        mouseX = qRound(event->position().x());
        mouseY = qRound(event->position().y());
        event->accept();
    }
    void mousePressEvent(QMouseEvent* event) override { HandleMouse(event, true); }
    void mouseReleaseEvent(QMouseEvent* event) override { HandleMouse(event, false); }

    static int MouseIndex(Qt::MouseButton button)
    {
        if (button == Qt::LeftButton) return 0;
        if (button == Qt::RightButton) return 1;
        if (button == Qt::MiddleButton) return 2;
        return -1;
    }
    void HandleMouse(QMouseEvent* event, bool isDown)
    {
        mouseX = qRound(event->position().x());
        mouseY = qRound(event->position().y());
        const int index = MouseIndex(event->button());
        if (index >= 0)
        {
            if (isDown && !mouseDown[index]) mousePressed[index] = true;
            if (!isDown && mouseDown[index]) mouseReleased[index] = true;
            mouseDown[index] = isDown;
        }
        event->accept();
    }

    void HandleKey(QKeyEvent* event, bool isDown)
    {
        if (event->isAutoRepeat()) return;
        const int special = MapSpecial(event->key());
        if (special >= 0)
        {
            if (isDown && !down[special]) pressed[special] = true;
            if (!isDown && down[special]) released[special] = true;
            down[special] = isDown;
        }
        // Use key identity, not text(), so releasing Shift/Ctrl cannot leave
        // a letter key stuck. This API is for ASCII keys, not text entry.
        const int key = event->key();
        if (key >= 0x20 && key < 0x7f)
        {
            const int index = CharacterIndex(static_cast<char>(key));
            if (isDown && !charDown[index]) charPressed[index] = true;
            if (!isDown && charDown[index]) charReleased[index] = true;
            charDown[index] = isDown;
        }
        event->accept();
    }
};


namespace small_detail
{
struct WindowAccess
{
    static void BlitRgba(Window& window, const std::uint8_t* pixels,
                         int sourceWidth, int sourceHeight, int bytesPerLine,
                         double x, double y, double width, double height)
    {
        window.CheckOpen();
        const QImage source(pixels, sourceWidth, sourceHeight, bytesPerLine,
                            QImage::Format_RGBA8888_Premultiplied);
        QPainter painter(&window.impl_->back);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
        painter.drawImage(QRectF(x, y, width, height), source);
    }
};

void BlitRgba(Window& window, const std::uint8_t* pixels,
              int sourceWidth, int sourceHeight, int bytesPerLine,
              double x, double y, double width, double height)
{
    if (!pixels) throw std::invalid_argument("Image pixel data is null.");
    if (sourceWidth <= 0 || sourceHeight <= 0 || bytesPerLine < sourceWidth * 4)
        throw std::invalid_argument("Image pixel layout is invalid.");
    CheckFinite({x, y, width, height});
    if (width < 0 || height < 0)
        throw std::invalid_argument("draw_image size cannot be negative.");
    if (width == 0 || height == 0) return;

    WindowAccess::BlitRgba(window, pixels, sourceWidth, sourceHeight,
                           bytesPerLine, x, y, width, height);
}
}

Window::Window() = default;
Window::~Window() { delete impl_; }

void Window::CheckOpen() const
{
    if (!impl_ || impl_->closed || impl_->back.isNull())
        throw std::runtime_error("The Window is not open. Call open(width, height) first.");
}

void Window::open(int width, int height)
{
    if (width <= 0 || height <= 0)
        throw std::invalid_argument("Window width and height must be positive.");
    auto* app = qobject_cast<QApplication*>(QCoreApplication::instance());
    if (!app || QThread::currentThread() != app->thread())
        throw std::runtime_error("Small C++ is not initialized. Call initialize_small() near the beginning of main().");

    QImage image(width, height, QImage::Format_ARGB32_Premultiplied);
    if (image.isNull()) throw std::runtime_error("Cannot allocate the Window image.");
    image.fill(ToQt(Black));
    if (!impl_) impl_ = new Impl;
    impl_->back = image;
    impl_->front = image;
    impl_->ResetKeys();
    impl_->closed = false;
    impl_->setFixedSize(width, height);
    impl_->setWindowTitle(QString::fromUtf8(title_.c_str(), title_.length()));
    impl_->show();
    impl_->activateWindow();
    impl_->setFocus();
    ProcessEvents();
}

void Window::set_title(const String& title)
{
    title_ = title;
    if (impl_ && !impl_->closed)
    {
        impl_->setWindowTitle(QString::fromUtf8(title.c_str(), title.length()));
        ProcessEvents();
    }
}

String Window::title() const
{
    return title_;
}


void Window::close() { if (impl_) impl_->close(); }
bool Window::is_open()
{
    ProcessEvents();
    return impl_ && !impl_->closed && impl_->isVisible();
}
int Window::width() const { return impl_ ? impl_->back.width() : 0; }
int Window::height() const { return impl_ ? impl_->back.height() : 0; }
void Window::clear(Color color) { CheckOpen(); impl_->back.fill(ToQt(color)); }

void Window::set_pixel(int x, int y, Color color)
{
    CheckOpen();
    if (x < 0 || x >= width() || y < 0 || y >= height())
        throw std::out_of_range("pixel position is outside the Window.");
    impl_->back.setPixelColor(x, y, ToQt(color));
}

void Window::draw_line(double x1, double y1, double x2, double y2, Color color)
{
    CheckOpen(); CheckFinite({x1, y1, x2, y2});
    QPainter painter(&impl_->back);
    painter.setPen(ToQt(color));
    painter.drawLine(QLineF(x1, y1, x2, y2));
}
void Window::draw_rectangle(double x, double y, double width, double height, Color color)
{
    CheckOpen(); CheckFinite({x, y, width, height});
    if (width < 0 || height < 0) throw std::invalid_argument("Rectangle size cannot be negative.");
    QPainter painter(&impl_->back);
    painter.setPen(ToQt(color));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRectF(x, y, width, height));
}
void Window::fill_rectangle(double x, double y, double width, double height, Color color)
{
    CheckOpen(); CheckFinite({x, y, width, height});
    if (width < 0 || height < 0) throw std::invalid_argument("Rectangle size cannot be negative.");
    QPainter painter(&impl_->back);
    painter.fillRect(QRectF(x, y, width, height), ToQt(color));
}
void Window::draw_circle(double x, double y, double radius, Color color)
{
    CheckOpen(); CheckFinite({x, y, radius});
    if (radius < 0) throw std::invalid_argument("Circle radius cannot be negative.");
    QPainter painter(&impl_->back);
    painter.setPen(ToQt(color));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(QPointF(x, y), radius, radius);
}
void Window::fill_circle(double x, double y, double radius, Color color)
{
    CheckOpen(); CheckFinite({x, y, radius});
    if (radius < 0) throw std::invalid_argument("Circle radius cannot be negative.");
    QPainter painter(&impl_->back);
    painter.setPen(Qt::NoPen);
    painter.setBrush(ToQt(color));
    painter.drawEllipse(QPointF(x, y), radius, radius);
}
void Window::draw_text(double x, double y, const String& text)
{
    draw_text(x, y, text, White, 16);
}
void Window::draw_text(double x, double y, const String& text, Color color, int size)
{
    CheckOpen(); CheckFinite({x, y});
    if (size <= 0) throw std::invalid_argument("Text size must be positive.");
    QPainter painter(&impl_->back);
    painter.setPen(ToQt(color));
    QFont font = painter.font();
    font.setPixelSize(size);
    painter.setFont(font);
    painter.drawText(QPointF(x, y + QFontMetricsF(font).ascent()),
                     QString::fromUtf8(text.c_str(), text.length()));
}
void Window::show()
{
    CheckOpen();
    // QImage uses copy-on-write. The next drawing operation detaches back;
    // front keeps the last submitted image without an unconditional copy.
    impl_->front = impl_->back;
    impl_->repaint();
    // clear the OLD frame's edge flags before processing the NEW events.
    impl_->BeginNextFrame();
    ProcessEvents();
}

bool Window::key_down(Key key) const { return impl_ && impl_->down[SpecialIndex(key)]; }
bool Window::key_pressed(Key key) const { return impl_ && impl_->pressed[SpecialIndex(key)]; }
bool Window::key_released(Key key) const { return impl_ && impl_->released[SpecialIndex(key)]; }
bool Window::key_down(char key) const { return impl_ && impl_->charDown[CharacterIndex(key)]; }
bool Window::key_pressed(char key) const { return impl_ && impl_->charPressed[CharacterIndex(key)]; }
bool Window::key_released(char key) const { return impl_ && impl_->charReleased[CharacterIndex(key)]; }

namespace
{
int MouseButtonIndex(MouseButton button)
{
    switch (button)
    {
    case MouseButton::Left: return 0;
    case MouseButton::Right: return 1;
    case MouseButton::Middle: return 2;
    }
    return 0;
}
}
int Window::mouse_x() const { return impl_ ? impl_->mouseX : 0; }
int Window::mouse_y() const { return impl_ ? impl_->mouseY : 0; }
bool Window::mouse_down(MouseButton button) const { return impl_ && impl_->mouseDown[MouseButtonIndex(button)]; }
bool Window::mouse_pressed(MouseButton button) const { return impl_ && impl_->mousePressed[MouseButtonIndex(button)]; }
bool Window::mouse_released(MouseButton button) const { return impl_ && impl_->mouseReleased[MouseButtonIndex(button)]; }

} // namespace Small

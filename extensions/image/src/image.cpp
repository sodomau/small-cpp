#include "small/image.h"
#include "small_internal.h"

#include <QColor>
#include <QImage>
#include <cmath>
#include <stdexcept>
#include <utility>

namespace Small
{
namespace
{
Color FromQt(const QColor& color) { return rgb(color.red(), color.green(), color.blue()); }
QColor ToQt(Color color) { return QColor(color.red(), color.green(), color.blue()); }
void CheckPixel(const QImage& image, int x, int y)
{
    if (x < 0 || x >= image.width() || y < 0 || y >= image.height())
        throw std::out_of_range("Image pixel position is outside the Image.");
}
}

struct Image::Impl { QImage image; };

Image::Image(int width, int height, Color fill) : impl_(new Impl)
{
    if (width <= 0 || height <= 0)
        throw std::invalid_argument("Image size must be positive.");
    impl_->image = QImage(width, height, QImage::Format_RGBA8888_Premultiplied);
    impl_->image.fill(ToQt(fill));
}
Image::~Image() { delete impl_; }
Image::Image(const Image& other) : impl_(new Impl{other.impl_->image}) {}
Image& Image::operator=(const Image& other)
{
    if (this != &other) impl_->image = other.impl_->image;
    return *this;
}
Image::Image(Image&& other) : impl_(other.impl_) { other.impl_ = new Impl; }
Image& Image::operator=(Image&& other)
{
    if (this != &other) { delete impl_; impl_ = other.impl_; other.impl_ = new Impl; }
    return *this;
}

Image load_image(const String& file_name)
{
    QImage loaded;
    if (!loaded.load(file_name.c_str()))
        throw std::runtime_error("Could not load image: " + std::string(file_name.c_str()) + ".");

    Image image(loaded.width(), loaded.height());
    image.impl_->image = loaded.convertToFormat(QImage::Format_RGBA8888_Premultiplied);
    return image;
}

void save_image(const Image& image, const String& file_name)
{
    if (!image.impl_->image.save(file_name.c_str()))
        throw std::runtime_error("Could not save image: " + std::string(file_name.c_str()) + ".");
}

int Image::width() const { return impl_->image.width(); }
int Image::height() const { return impl_->image.height(); }

Color Image::pixel(int x, int y) const
{
    CheckPixel(impl_->image, x, y);
    return FromQt(impl_->image.pixelColor(x, y));
}
int Image::alpha(int x, int y) const
{
    CheckPixel(impl_->image, x, y);
    return impl_->image.pixelColor(x, y).alpha();
}
void Image::set_pixel(int x, int y, Color color)
{
    set_pixel(x, y, color, 255);
}
void Image::set_pixel(int x, int y, Color color, int alpha)
{
    CheckPixel(impl_->image, x, y);
    if (alpha < 0 || alpha > 255)
        throw std::out_of_range("Image alpha must be between 0 and 255.");
    QColor q = ToQt(color);
    q.setAlpha(alpha);
    impl_->image.setPixelColor(x, y, q);
}

void draw_image(Window& window, const Image& image, double x, double y)
{
    draw_image(window, image, x, y, image.width(), image.height());
}
void draw_image(Window& window, const Image& image, double x, double y,
               double width, double height)
{
    if (!std::isfinite(x) || !std::isfinite(y) ||
        !std::isfinite(width) || !std::isfinite(height))
        throw std::invalid_argument("draw_image values must be finite.");
    if (width < 0 || height < 0)
        throw std::invalid_argument("draw_image size cannot be negative.");
    if (width == 0 || height == 0) return;

    const QImage& q = image.impl_->image;
    small_detail::BlitRgba(window, q.constBits(), q.width(), q.height(),
                           q.bytesPerLine(), x, y, width, height);
}
}

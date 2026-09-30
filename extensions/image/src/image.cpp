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
Color FromQt(const QColor& color) { return RGB(color.red(), color.green(), color.blue()); }
QColor ToQt(Color color) { return QColor(color.Red(), color.Green(), color.Blue()); }
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

Image LoadImage(const String& filename)
{
    QImage loaded;
    if (!loaded.load(filename.c_str()))
        throw std::runtime_error("Could not load image: " + std::string(filename.c_str()) + ".");

    Image image(loaded.width(), loaded.height());
    image.impl_->image = loaded.convertToFormat(QImage::Format_RGBA8888_Premultiplied);
    return image;
}

void SaveImage(const Image& image, const String& filename)
{
    if (!image.impl_->image.save(filename.c_str()))
        throw std::runtime_error("Could not save image: " + std::string(filename.c_str()) + ".");
}

int Image::Width() const { return impl_->image.width(); }
int Image::Height() const { return impl_->image.height(); }

Color Image::Pixel(int x, int y) const
{
    CheckPixel(impl_->image, x, y);
    return FromQt(impl_->image.pixelColor(x, y));
}
int Image::Alpha(int x, int y) const
{
    CheckPixel(impl_->image, x, y);
    return impl_->image.pixelColor(x, y).alpha();
}
void Image::SetPixel(int x, int y, Color color)
{
    SetPixel(x, y, color, 255);
}
void Image::SetPixel(int x, int y, Color color, int alpha)
{
    CheckPixel(impl_->image, x, y);
    if (alpha < 0 || alpha > 255)
        throw std::out_of_range("Image alpha must be between 0 and 255.");
    QColor q = ToQt(color);
    q.setAlpha(alpha);
    impl_->image.setPixelColor(x, y, q);
}

void DrawImage(Window& window, const Image& image, double x, double y)
{
    DrawImage(window, image, x, y, image.Width(), image.Height());
}
void DrawImage(Window& window, const Image& image, double x, double y,
               double width, double height)
{
    if (!std::isfinite(x) || !std::isfinite(y) ||
        !std::isfinite(width) || !std::isfinite(height))
        throw std::invalid_argument("DrawImage values must be finite.");
    if (width < 0 || height < 0)
        throw std::invalid_argument("DrawImage size cannot be negative.");
    if (width == 0 || height == 0) return;

    const QImage& q = image.impl_->image;
    small_detail::BlitRgba(window, q.constBits(), q.width(), q.height(),
                           q.bytesPerLine(), x, y, width, height);
}
}

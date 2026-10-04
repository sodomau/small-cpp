#pragma once
#include <small.h>

namespace Small
{
class Image
{
public:
    Image(int width, int height, Color fill = Black);
    ~Image();

    Image(const Image& other);
    Image& operator=(const Image& other);
    Image(Image&& other);
    Image& operator=(Image&& other);

    int width() const;
    int height() const;

    Color pixel(int x, int y) const;
    int alpha(int x, int y) const;
    void set_pixel(int x, int y, Color color);
    void set_pixel(int x, int y, Color color, int alpha);

private:
    friend Image load_image(const String&);
    friend void save_image(const Image&, const String&);
    friend void draw_image(Window&, const Image&, double, double);
    friend void draw_image(Window&, const Image&, double, double, double, double);
    struct Impl;
    Impl* impl_;
};

// Relationships between independent abstractions are free functions.
Image load_image(const String& file_name);
void save_image(const Image& image, const String& file_name);

// Core Window never depends on Image.
void draw_image(Window& window, const Image& image, double x, double y);
void draw_image(Window& window, const Image& image, double x, double y,
               double width, double height);
}

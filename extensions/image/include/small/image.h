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

    int Width() const;
    int Height() const;

    Color Pixel(int x, int y) const;
    int Alpha(int x, int y) const;
    void SetPixel(int x, int y, Color color);
    void SetPixel(int x, int y, Color color, int alpha);

private:
    friend Image LoadImage(const String&);
    friend void SaveImage(const Image&, const String&);
    friend void DrawImage(Window&, const Image&, double, double);
    friend void DrawImage(Window&, const Image&, double, double, double, double);
    struct Impl;
    Impl* impl_;
};

// Relationships between independent abstractions are free functions.
Image LoadImage(const String& filename);
void SaveImage(const Image& image, const String& filename);

// Core Window never depends on Image.
void DrawImage(Window& window, const Image& image, double x, double y);
void DrawImage(Window& window, const Image& image, double x, double y,
               double width, double height);
}

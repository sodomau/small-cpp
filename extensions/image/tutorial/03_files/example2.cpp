#include <small/image.h>

void SmallMain()
{
    Image image(120, 80, Yellow);
    SaveImage(image, "picture.png");

    Image copy = LoadImage("picture.png");

    Print(copy.Width(), " x ", copy.Height());
}

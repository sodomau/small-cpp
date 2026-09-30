#include <small/image.h>
void SmallMain()
{
    Image image(50, 50, Cyan);
    SaveImage(image, "cyan.png");
    Image loaded = LoadImage("cyan.png");
    Print(loaded.Width(), " x ", loaded.Height());
}

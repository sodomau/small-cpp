#include <small/image.h>
void SmallMain()
{
    Image image(20, 20, White);
    SaveImage(image, "original.png");
    Image changed = LoadImage("original.png");
    changed.SetPixel(0, 0, Magenta);
    SaveImage(changed, "changed.png");
}

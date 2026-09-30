#include <small/image.h>
void SmallMain()
{
    Image image(20, 20, White);
    SaveImage(image, "original.png");
    // Load, change one pixel, and save as changed.png.
}

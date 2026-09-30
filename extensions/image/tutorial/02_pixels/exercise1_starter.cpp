#include <small/image.h>
void SmallMain()
{
    Image image(100, 100, Black);
    // Draw a yellow diagonal with SetPixel.
    SaveImage(image, "diagonal.png");
}

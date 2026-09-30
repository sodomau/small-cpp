#include <small/image.h>
void SmallMain()
{
    Image image(100, 100, Black);
    for (int i = 0; i < 100; i++)
        image.SetPixel(i, i, Yellow);
    SaveImage(image, "diagonal.png");
}

#include <small/image.h>
void SmallMain()
{
    Image image(30, 30, Red);
    Color color = image.Pixel(10, 10);
    Print(color.Red());
}

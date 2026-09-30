#include <small/image.h>

void SmallMain()
{
    Image image(200, 200, Black);

    for (int y = 0; y < image.Height(); y++)
        for (int x = 0; x < image.Width(); x++)
            if ((x / 20 + y / 20) % 2 == 0)
                image.SetPixel(x, y, White);

    SaveImage(image, "checker.png");
    Print("Saved checker.png");
}

#include <small/image.h>

void SmallMain()
{
    Image image(256, 256, Black);

    for (int y = 0; y < image.Height(); y++)
        for (int x = 0; x < image.Width(); x++)
            image.SetPixel(x, y, RGB(x, y, 180));

    Window window;
    window.Open(520, 320);

    while (window.IsOpen())
    {
        window.Clear(Black);
        DrawImage(window, image, 32, 32);
        window.Show();
    }
}

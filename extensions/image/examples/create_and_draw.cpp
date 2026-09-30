#include <small/image.h>

void SmallMain()
{
    Image image(160, 120, Blue);

    for (int y = 20; y < 100; y++)
        for (int x = 20; x < 140; x++)
            image.SetPixel(x, y, Yellow);

    Window window;
    window.Open(640, 400);

    while (window.IsOpen())
    {
        window.Clear(Black);
        DrawImage(window, image, 80, 80);
        DrawImage(window, image, 300, 80, 240, 180);
        window.Show();
    }
}

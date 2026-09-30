#include <small/image.h>

void SmallMain()
{
    Image made(200, 120, Cyan);

    for (int y = 30; y < 90; y++)
        for (int x = 40; x < 160; x++)
            made.SetPixel(x, y, Magenta);

    SaveImage(made, "small_image_test.png");

    Image loaded = LoadImage("small_image_test.png");
    Print("Loaded: ", loaded.Width(), " x ", loaded.Height());

    Window window;
    window.Open(500, 300);

    while (window.IsOpen())
    {
        window.Clear(Black);
        DrawImage(window, loaded, 150, 80);
        window.Show();
    }
}

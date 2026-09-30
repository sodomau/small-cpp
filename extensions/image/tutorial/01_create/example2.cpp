#include <small/image.h>

void SmallMain()
{
    Image image(100, 100, Red);
    Print(image.Width(), " x ", image.Height());

    Window window;
    window.Open(400, 250);

    while (window.IsOpen())
    {
        window.Clear(White);
        DrawImage(window, image, 150, 75);
        window.Show();
    }
}

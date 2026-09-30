#include <small/image.h>

void SmallMain()
{
    Image image = LoadImage("cat.png");
    Print(image.Width(), " x ", image.Height());

    Window window;
    window.Open(800, 600);

    while (window.IsOpen())
    {
        window.Clear(Black);
        DrawImage(window, image, 100, 100);
        window.Show();
    }
}

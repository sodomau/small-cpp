#include <small/image.h>
void SmallMain()
{
    Image image(120, 80, Green);
    Window window;
    window.Open(600, 300);
    while (window.IsOpen())
    {
        window.Clear(Black);
        DrawImage(window, image, 40, 60);
        DrawImage(window, image, 260, 40, 240, 160);
        window.Show();
    }
}

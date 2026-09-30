#include <small/image.h>
void SmallMain()
{
    Image image(120, 80, Green);
    Window window;
    window.Open(600, 300);
    while (window.IsOpen())
    {
        window.Clear(Black);
        // Draw twice here.
        window.Show();
    }
}

#include <small/image.h>
void small_main()
{
    Image image(120, 80, Green);
    Window window;
    window.open(600, 300);
    while (window.is_open())
    {
        window.clear(Black);
        // Draw twice here.
        window.show();
    }
}

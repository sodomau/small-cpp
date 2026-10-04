#include <small/image.h>
void small_main()
{
    Image image(120, 80, Green);
    Window window;
    window.open(600, 300);
    while (window.is_open())
    {
        window.clear(Black);
        draw_image(window, image, 40, 60);
        draw_image(window, image, 260, 40, 240, 160);
        window.show();
    }
}

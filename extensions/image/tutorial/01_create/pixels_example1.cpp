#include <small/image.h>

void small_main()
{
    Image image(256, 256, Black);

    for (int y = 0; y < image.height(); y++)
        for (int x = 0; x < image.width(); x++)
            image.set_pixel(x, y, rgb(x, y, 180));

    Window window;
    window.open(520, 320);

    while (window.is_open())
    {
        window.clear(Black);
        draw_image(window, image, 32, 32);
        window.show();
    }
}

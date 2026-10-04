#include <small/image.h>

void small_main()
{
    Image image(160, 120, Blue);

    for (int y = 20; y < 100; y++)
        for (int x = 20; x < 140; x++)
            image.set_pixel(x, y, Yellow);

    Window window;
    window.open(640, 400);

    while (window.is_open())
    {
        window.clear(Black);
        draw_image(window, image, 80, 80);
        draw_image(window, image, 300, 80, 240, 180);
        window.show();
    }
}

#include <small/image.h>

void small_main()
{
    Image image(100, 100, Red);
    print(image.width(), " x ", image.height());

    Window window;
    window.open(400, 250);

    while (window.is_open())
    {
        window.clear(White);
        draw_image(window, image, 150, 75);
        window.show();
    }
}

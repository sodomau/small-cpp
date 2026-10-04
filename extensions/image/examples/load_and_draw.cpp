#include <small/image.h>

void small_main()
{
    Image image = load_image("cat.png");
    print(image.width(), " x ", image.height());

    Window window;
    window.open(800, 600);

    while (window.is_open())
    {
        window.clear(Black);
        draw_image(window, image, 100, 100);
        window.show();
    }
}

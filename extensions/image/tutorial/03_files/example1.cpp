#include <small/image.h>

void small_main()
{
    Image made(200, 120, Cyan);

    for (int y = 30; y < 90; y++)
        for (int x = 40; x < 160; x++)
            made.set_pixel(x, y, Magenta);

    save_image(made, "small_image_test.png");

    Image loaded = load_image("small_image_test.png");
    print("Loaded: ", loaded.width(), " x ", loaded.height());

    Window window;
    window.open(500, 300);

    while (window.is_open())
    {
        window.clear(Black);
        draw_image(window, loaded, 150, 80);
        window.show();
    }
}

#include <small/image.h>

void small_main()
{
    Image image(200, 200, Black);

    for (int y = 0; y < image.height(); y++)
        for (int x = 0; x < image.width(); x++)
            if ((x / 20 + y / 20) % 2 == 0)
                image.set_pixel(x, y, White);

    save_image(image, "checker.png");
    print("Saved checker.png");
}

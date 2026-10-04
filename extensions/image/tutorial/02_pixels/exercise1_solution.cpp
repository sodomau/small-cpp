#include <small/image.h>
void small_main()
{
    Image image(100, 100, Black);
    for (int i = 0; i < 100; i++)
        image.set_pixel(i, i, Yellow);
    save_image(image, "diagonal.png");
}

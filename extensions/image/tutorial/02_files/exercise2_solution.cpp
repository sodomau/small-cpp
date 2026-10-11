#include <small/image.h>
void small_main()
{
    Image image(20, 20, White);
    save_image(image, "original.png");
    Image changed = load_image("original.png");
    changed.set_pixel(0, 0, Magenta);
    save_image(changed, "changed.png");
}

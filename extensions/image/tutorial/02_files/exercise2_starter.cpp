#include <small/image.h>
void small_main()
{
    Image image(20, 20, White);
    save_image(image, "original.png");
    // Load, change one pixel, and save as changed.png.
}

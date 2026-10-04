#include <small/image.h>
void small_main()
{
    Image image(100, 100, Black);
    // Draw a yellow diagonal with set_pixel.
    save_image(image, "diagonal.png");
}

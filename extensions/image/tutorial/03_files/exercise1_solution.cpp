#include <small/image.h>
void small_main()
{
    Image image(50, 50, Cyan);
    save_image(image, "cyan.png");
    Image loaded = load_image("cyan.png");
    print(loaded.width(), " x ", loaded.height());
}

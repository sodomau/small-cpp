#include <small/image.h>

void small_main()
{
    Image image(120, 80, Yellow);
    save_image(image, "picture.png");

    Image copy = load_image("picture.png");

    print(copy.width(), " x ", copy.height());
}

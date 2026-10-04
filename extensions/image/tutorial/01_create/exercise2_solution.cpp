#include <small/image.h>
void small_main()
{
    Image image(64, 48, Blue);
    print(image.width(), " x ", image.height());
}

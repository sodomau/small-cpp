#include <small/image.h>
void small_main()
{
    Image image(30, 30, Red);
    Color color = image.pixel(10, 10);
    print(color.red());
}

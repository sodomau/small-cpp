#include <small/image.h>
void SmallMain()
{
    Image image(64, 48, Blue);
    Print(image.Width(), " x ", image.Height());
}

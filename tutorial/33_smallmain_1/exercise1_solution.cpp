#include <small.h>

int main()
{
    Small::initialize_small();

    Small::print("Hello from main!");

    Small::shutdown_small();
    return 0;
}

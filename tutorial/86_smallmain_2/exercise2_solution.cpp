#include <small.h>

int main(int argc, char* argv[])
{
    Small::initialize_small(argc, argv);

    Small::print("argc: ", argc);

    Small::shutdown_small();
    return 0;
}

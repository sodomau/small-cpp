#include <small.h>

int main(int argc, char* argv[])
{
    Small::InitializeSmall(argc, argv);

    Small::Print("argc: ", argc);

    Small::ShutdownSmall();
    return 0;
}

#include <small.h>

int main()
{
    Small::InitializeSmall();

    Small::Print("Hello from main!");

    Small::ShutdownSmall();
    return 0;
}

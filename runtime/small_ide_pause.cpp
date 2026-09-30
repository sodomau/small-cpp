#include <cstdlib>
#include <iostream>

namespace
{
void PauseConsoleAtExit()
{
#ifdef _WIN32
    std::cout << "\nPress Enter to exit...";
    std::cout.flush();
    std::cin.clear();
    std::cin.get();
#endif
}

struct IdePauseRegistration
{
    IdePauseRegistration()
    {
        std::atexit(PauseConsoleAtExit);
    }
};

// This translation unit is linked only into programs launched by Small IDE.
// Its presence in the executable is the policy switch; Small runtime itself
// knows nothing about the IDE pause behavior.
IdePauseRegistration registration;
}

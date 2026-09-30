#include <cstdlib>
#include <iostream>

namespace
{
void PauseConsoleAtExit()
{
#ifdef _WIN32
    if (std::getenv("SMALL_TEST_NO_CONSOLE_PAUSE"))
        return;
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

// This object file is linked directly into programs launched by Small IDE.
// Its presence in the executable is the policy switch; Small runtime itself
// knows nothing about the IDE pause behavior.
IdePauseRegistration registration;
}

#include "small_internal.h"

#ifdef _WIN32

#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include <cstdlib>
#include <iostream>
#include <string>

namespace Small::small_detail
{
void InitializePlatform()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleTitleW(L"Small C++");
}

void PauseConsoleBeforeExit()
{
    if (std::getenv("SMALL_TEST_NO_CONSOLE_PAUSE"))
        return;

    std::cout << "\nPress Enter to close..." << std::flush;
    std::string line;
    std::getline(std::cin, line);
}
}

#endif

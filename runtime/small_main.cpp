#include "small.h"

#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
    int result = 0;
    bool initialized = false;

    try
    {
        Small::initialize_small(argc, argv);
        initialized = true;
        small_main();
    }
    catch (const std::exception& error)
    {
        std::cerr << "\nRuntime error: " << error.what() << '\n';
        if (const char* path = std::getenv("SMALL_RUNTIME_ERROR_FILE"))
            std::ofstream(path) << error.what();
        result = 1;
    }
    catch (...)
    {
        const char* message = "an unknown exception was thrown.";
        std::cerr << "\nRuntime error: " << message << '\n';
        if (const char* path = std::getenv("SMALL_RUNTIME_ERROR_FILE"))
            std::ofstream(path) << message;
        result = 1;
    }

    if (initialized)
        Small::shutdown_small();

    return result;
}

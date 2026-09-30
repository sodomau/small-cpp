#include "small_internal.h"

#ifndef _WIN32

namespace Small::small_detail
{
void InitializePlatform()
{
    // No platform-specific console setup is currently required.
}

void PauseConsoleBeforeExit()
{
    // The Windows IDE launches a separate console and pauses it for learners.
    // Other platforms do not need that behavior here.
}
}

#endif

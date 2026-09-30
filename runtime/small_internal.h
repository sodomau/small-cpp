#pragma once
#include <cstdint>

namespace Small { class Window; }
// Runtime implementation only. Never force-included into a learner program.
namespace Small::small_detail
{
    void ShutdownAudio();
    void InitializePlatform();
    void PauseConsoleBeforeExit();

    // Extension-facing rendering bridge. Core knows only raw premultiplied RGBA
    // pixels, never extension types such as Image.
    void BlitRgba(Window& window, const std::uint8_t* pixels,
                  int sourceWidth, int sourceHeight, int bytesPerLine,
                  double x, double y, double width, double height);

    struct WindowAccess;
}

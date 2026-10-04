#include <small.h>

int main(int argc, char* argv[])
{
    Small::initialize_small(argc, argv);

    {
        Small::Window window;
        window.set_title("Real main()");
        window.open(500, 300);

        while (window.is_open())
        {
            window.clear(Small::Black);
            window.draw_text(30, 80, "This is ordinary C++ main()");
            window.show();
        }
    } // Destroy Window before shutting down the runtime.
    Small::shutdown_small();
    return 0;
}

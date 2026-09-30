#include <small.h>

int main(int argc, char* argv[])
{
    Small::InitializeSmall(argc, argv);

    {
        Small::Window window;
        window.SetTitle("Real main()");
        window.Open(500, 300);

        while (window.IsOpen())
        {
            window.Clear(Small::Black);
            window.DrawText(30, 80, "This is ordinary C++ main()");
            window.Show();
        }
    } // Destroy Window before shutting down the runtime.
    Small::ShutdownSmall();
    return 0;
}

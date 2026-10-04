void small_main()
{
    Window window;
    window.open(500, 500);

    window.clear(White);

    // Draw your face here.

    window.show();
    while (window.is_open())
        window.show();
}

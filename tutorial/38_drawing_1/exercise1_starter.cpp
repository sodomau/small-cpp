void small_main()
{
    Window window;
    window.open(300, 500);

    window.clear(White);

    // Draw a traffic light here.

    window.show();
    while (window.is_open())
        window.show();
}

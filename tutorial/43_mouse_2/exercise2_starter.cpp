void small_main()
{
    Window window;
    window.open(640, 480);

    while (window.is_open())
    {
        window.clear(White);

        // Left = red, Right = blue.

        window.show();
    }
}

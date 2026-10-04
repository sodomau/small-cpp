void small_main()
{
    Window window;
    window.open(640, 480);

    bool is_big = false;

    while (window.is_open())
    {
        // Toggle is_big when Space is pressed.

        window.clear(Black);

        if (is_big)
            window.fill_circle(320, 240, 60, Yellow);
        else
            window.fill_circle(320, 240, 20, Yellow);

        window.show();
    }
}

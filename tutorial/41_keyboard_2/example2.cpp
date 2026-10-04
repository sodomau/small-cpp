void small_main()
{
    Window window;
    window.open(640, 480);

    bool is_red = true;

    while (window.is_open())
    {
        if (window.key_pressed(Key::Space))
            is_red = !is_red;

        window.clear(Black);

        if (is_red)
            window.fill_circle(320, 240, 60, Red);
        else
            window.fill_circle(320, 240, 60, Blue);

        window.show();
    }
}

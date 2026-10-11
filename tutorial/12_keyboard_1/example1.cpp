void small_main()
{
    Window window;
    window.open(640, 480);

    double x = 320;
    double y = 240;

    while (window.is_open())
    {
        if (window.key_down(Key::Left))
            x = x - 2;
        if (window.key_down(Key::Right))
            x = x + 2;
        if (window.key_down(Key::Up))
            y = y - 2;
        if (window.key_down(Key::Down))
            y = y + 2;

        window.clear(Black);
        window.fill_circle(x, y, 20, Yellow);
        window.show();
    }
}

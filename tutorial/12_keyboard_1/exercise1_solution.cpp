void small_main()
{
    Window window;
    window.open(640, 480);

    double x = 320;
    double y = 240;

    while (window.is_open())
    {
        if (window.key_down('A')) x = x - 2;
        if (window.key_down('D')) x = x + 2;
        if (window.key_down('W')) y = y - 2;
        if (window.key_down('S')) y = y + 2;

        window.clear(Black);
        window.fill_circle(x, y, 20, Cyan);
        window.show();
    }
}

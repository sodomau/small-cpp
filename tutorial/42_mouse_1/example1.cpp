void small_main()
{
    Window window;
    window.open(640, 480);

    while (window.is_open())
    {
        window.clear(White);
        window.fill_circle(window.mouse_x(), window.mouse_y(), 12, Red);
        window.show();
    }
}

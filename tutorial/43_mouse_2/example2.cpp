void small_main()
{
    Window window;
    window.open(640, 480);

    while (window.is_open())
    {
        window.clear(White);

        if (window.mouse_down(MouseButton::Left))
            window.fill_circle(window.mouse_x(), window.mouse_y(), 30, Blue);
        else
            window.draw_circle(window.mouse_x(), window.mouse_y(), 30, Black);

        window.show();
    }
}

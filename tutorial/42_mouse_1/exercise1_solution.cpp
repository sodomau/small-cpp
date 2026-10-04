void small_main()
{
    Window window;
    window.open(640, 480);

    while (window.is_open())
    {
        window.clear(Black);

        if (window.mouse_down(MouseButton::Left))
            window.fill_circle(window.mouse_x(), window.mouse_y(), 25, Yellow);
        else
            window.fill_circle(window.mouse_x(), window.mouse_y(), 8, Gray);

        window.show();
    }
}

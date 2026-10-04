void small_main()
{
    Window window;
    window.open(640, 480);

    while (window.is_open())
    {
        if (window.mouse_pressed(MouseButton::Left))
            print("Left button pressed");

        if (window.mouse_released(MouseButton::Right))
            print("Right button released");

        if (window.mouse_down(MouseButton::Middle))
            print("Middle button is down");

        window.clear(White);
        window.fill_circle(window.mouse_x(), window.mouse_y(), 8, Red);
        window.show();
    }
}

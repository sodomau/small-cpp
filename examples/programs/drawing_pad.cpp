void small_main()
{
    Window window;
    window.open(800, 600);

    window.clear(White);
    window.show();

    // Left draws, right erases, and Space clears the canvas.
    while (window.is_open())
    {
        if (window.mouse_down(MouseButton::Left))
            window.fill_circle(window.mouse_x(), window.mouse_y(), 8, Blue);

        if (window.mouse_down(MouseButton::Right))
            window.fill_circle(window.mouse_x(), window.mouse_y(), 16, White);

        if (window.key_pressed(Key::Space))
            window.clear(White);

        window.show();
    }
}

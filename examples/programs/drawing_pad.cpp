void SmallMain()
{
    Window window;
    window.Open(800, 600);

    window.Clear(White);
    window.Show();

    // Left draws, right erases, and Space clears the canvas.
    while (window.IsOpen())
    {
        if (window.MouseDown(MouseButton::Left))
            window.FillCircle(window.MouseX(), window.MouseY(), 8, Blue);

        if (window.MouseDown(MouseButton::Right))
            window.FillCircle(window.MouseX(), window.MouseY(), 16, White);

        if (window.KeyPressed(Key::Space))
            window.Clear(White);

        window.Show();
    }
}

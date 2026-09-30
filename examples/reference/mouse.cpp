void SmallMain()
{
    Window window;
    window.Open(640, 480);

    while (window.IsOpen())
    {
        if (window.MousePressed(MouseButton::Left))
            Print("Left button pressed");

        if (window.MouseReleased(MouseButton::Right))
            Print("Right button released");

        if (window.MouseDown(MouseButton::Middle))
            Print("Middle button is down");

        window.Clear(White);
        window.FillCircle(window.MouseX(), window.MouseY(), 8, Red);
        window.Show();
    }
}

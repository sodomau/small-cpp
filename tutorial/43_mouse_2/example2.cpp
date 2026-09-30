void SmallMain()
{
    Window window;
    window.Open(640, 480);

    while (window.IsOpen())
    {
        window.Clear(White);

        if (window.MouseDown(MouseButton::Left))
            window.FillCircle(window.MouseX(), window.MouseY(), 30, Blue);
        else
            window.DrawCircle(window.MouseX(), window.MouseY(), 30, Black);

        window.Show();
    }
}

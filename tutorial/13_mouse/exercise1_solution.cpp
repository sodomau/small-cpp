void SmallMain()
{
    Window window;
    window.Open(640, 480);

    while (window.IsOpen())
    {
        window.Clear(Black);

        if (window.MouseDown(MouseButton::Left))
            window.FillCircle(window.MouseX(), window.MouseY(), 25, Yellow);
        else
            window.FillCircle(window.MouseX(), window.MouseY(), 8, Gray);

        window.Show();
    }
}

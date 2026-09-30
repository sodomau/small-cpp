void SmallMain()
{
    Window window;
    window.Open(640, 480);

    while (window.IsOpen())
    {
        window.Clear(White);
        window.FillCircle(window.MouseX(), window.MouseY(), 12, Red);
        window.Show();
    }
}

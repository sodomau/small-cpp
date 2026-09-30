void SmallMain()
{
    Window window;
    window.Open(640, 480);

    double x = 320;
    double y = 240;

    while (window.IsOpen())
    {
        if (window.KeyDown('A')) x = x - 2;
        if (window.KeyDown('D')) x = x + 2;
        if (window.KeyDown('W')) y = y - 2;
        if (window.KeyDown('S')) y = y + 2;

        window.Clear(Black);
        window.FillCircle(x, y, 20, Cyan);
        window.Show();
    }
}

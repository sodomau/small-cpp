void SmallMain()
{
    Window window;
    window.Open(640, 480);

    double x = 320;
    double y = 240;

    while (window.IsOpen())
    {
        if (window.KeyDown(Key::Left))
            x = x - 2;
        if (window.KeyDown(Key::Right))
            x = x + 2;
        if (window.KeyDown(Key::Up))
            y = y - 2;
        if (window.KeyDown(Key::Down))
            y = y + 2;

        window.Clear(Black);
        window.FillCircle(x, y, 20, Yellow);
        window.Show();
    }
}

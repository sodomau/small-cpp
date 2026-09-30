void SmallMain()
{
    Window window;
    window.Open(640, 480);

    double y = 100;
    double speed = 3;

    while (window.IsOpen())
    {
        y = y + speed;

        if (y > 460 || y < 20)
            speed = -speed;

        window.Clear(Black);
        window.FillCircle(320, y, 20, Green);
        window.Show();
        Sleep(0.01);
    }
}

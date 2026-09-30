void SmallMain()
{
    Window window;
    window.Open(640, 480);

    double x1 = 50;
    double x2 = 200;
    double speed1 = 2;
    double speed2 = 4;

    while (window.IsOpen())
    {
        x1 = x1 + speed1;
        x2 = x2 + speed2;

        if (x1 > 655) x1 = -15;
        if (x2 > 655) x2 = -15;

        window.Clear(Black);
        window.FillCircle(x1, 180, 15, Yellow);
        window.FillCircle(x2, 300, 15, Cyan);
        window.Show();
        Sleep(0.01);
    }
}

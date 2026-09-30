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
        // Update both balls.

        window.Clear(Black);
        window.FillCircle(x1, 180, 15, Yellow);
        window.FillCircle(x2, 300, 15, Cyan);
        window.Show();
        Sleep(0.01);
    }
}

void SmallMain()
{
    Window window;
    window.Open(640, 480);

    double x = 100;
    double speed = 3;

    while (window.IsOpen())
    {
        x = x + speed;

        if (x > 620 || x < 20)
            speed = -speed;

        window.Clear(Black);
        window.FillCircle(x, 240, 20, Cyan);
        window.Show();
        Sleep(0.01);
    }
}

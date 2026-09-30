void SmallMain()
{
    Window window;
    window.Open(640, 480);

    double y = 100;
    double speed = 150;
    StopWatch watch;

    while (window.IsOpen())
    {
        double dt = watch.Elapsed();
        watch.Reset();

        y = y + speed * dt;

        if (y > 460 || y < 20)
            speed = -speed;

        window.Clear(Black);
        window.FillCircle(320, y, 20, Green);
        window.Show();
    }
}

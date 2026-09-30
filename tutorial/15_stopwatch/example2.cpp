void SmallMain()
{
    Window window;
    window.Open(640, 480);

    double x = 50;
    double speed = 200;

    StopWatch watch;

    while (window.IsOpen())
    {
        double dt = watch.Elapsed();
        watch.Reset();

        x = x + speed * dt;

        if (x > 620 || x < 20)
            speed = -speed;

        window.Clear(Black);
        window.FillCircle(x, 240, 20, Yellow);
        window.Show();
    }
}

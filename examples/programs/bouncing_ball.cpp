void SmallMain()
{
    Window window;
    window.Open(640, 480);

    double x = 100;
    double y = 100;
    double vx = 180;
    double vy = 140;
    double radius = 20;

    StopWatch watch;

    while (window.IsOpen())
    {
        // Use elapsed time so speed does not depend on frame rate.
        double dt = watch.Elapsed();
        watch.Reset();

        x = x + vx * dt;
        y = y + vy * dt;

        if (x - radius < 0)
        {
            x = radius;
            vx = -vx;
            PlaySound(Sound::Pop);
        }
        if (x + radius > window.Width())
        {
            x = window.Width() - radius;
            vx = -vx;
            PlaySound(Sound::Pop);
        }
        if (y - radius < 0)
        {
            y = radius;
            vy = -vy;
            PlaySound(Sound::Pop);
        }
        if (y + radius > window.Height())
        {
            y = window.Height() - radius;
            vy = -vy;
            PlaySound(Sound::Pop);
        }

        window.Clear(Black);
        window.FillCircle(x, y, radius, Yellow);
        window.Show();
    }
}

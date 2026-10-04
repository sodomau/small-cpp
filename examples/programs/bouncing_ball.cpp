void small_main()
{
    Window window;
    window.open(640, 480);

    double x = 100;
    double y = 100;
    double vx = 180;
    double vy = 140;
    double radius = 20;

    StopWatch watch;

    while (window.is_open())
    {
        // Use elapsed time so speed does not depend on frame rate.
        double dt = watch.elapsed();
        watch.reset();

        x = x + vx * dt;
        y = y + vy * dt;

        if (x - radius < 0)
        {
            x = radius;
            vx = -vx;
            play_sound(Sound::Pop);
        }
        if (x + radius > window.width())
        {
            x = window.width() - radius;
            vx = -vx;
            play_sound(Sound::Pop);
        }
        if (y - radius < 0)
        {
            y = radius;
            vy = -vy;
            play_sound(Sound::Pop);
        }
        if (y + radius > window.height())
        {
            y = window.height() - radius;
            vy = -vy;
            play_sound(Sound::Pop);
        }

        window.clear(Black);
        window.fill_circle(x, y, radius, Yellow);
        window.show();
    }
}

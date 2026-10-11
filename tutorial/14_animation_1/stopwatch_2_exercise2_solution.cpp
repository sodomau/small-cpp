void small_main()
{
    Window window;
    window.open(640, 480);

    double y = 100;
    double speed = 150;
    StopWatch watch;

    while (window.is_open())
    {
        double dt = watch.elapsed();
        watch.reset();

        y = y + speed * dt;

        if (y > 460 || y < 20)
            speed = -speed;

        window.clear(Black);
        window.fill_circle(320, y, 20, Green);
        window.show();
    }
}

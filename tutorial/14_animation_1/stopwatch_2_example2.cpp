void small_main()
{
    Window window;
    window.open(640, 480);

    double x = 50;
    double speed = 200;

    StopWatch watch;

    while (window.is_open())
    {
        double dt = watch.elapsed();
        watch.reset();

        x = x + speed * dt;

        if (x > 620 || x < 20)
            speed = -speed;

        window.clear(Black);
        window.fill_circle(x, 240, 20, Yellow);
        window.show();
    }
}

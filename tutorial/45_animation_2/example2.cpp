void small_main()
{
    Window window;
    window.open(640, 480);

    double x = 100;
    double speed = 3;

    while (window.is_open())
    {
        x = x + speed;

        if (x > 620 || x < 20)
            speed = -speed;

        window.clear(Black);
        window.fill_circle(x, 240, 20, Cyan);
        window.show();
        sleep(0.01);
    }
}

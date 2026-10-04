void small_main()
{
    Window window;
    window.open(640, 480);

    double y = 100;
    double speed = 3;

    while (window.is_open())
    {
        y = y + speed;

        if (y > 460 || y < 20)
            speed = -speed;

        window.clear(Black);
        window.fill_circle(320, y, 20, Green);
        window.show();
        sleep(0.01);
    }
}

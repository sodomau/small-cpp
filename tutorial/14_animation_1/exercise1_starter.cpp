void small_main()
{
    Window window;
    window.open(640, 480);

    double y = 100;
    double speed = 3;

    while (window.is_open())
    {
        // Update y and bounce.

        window.clear(Black);
        window.fill_circle(320, y, 20, Green);
        window.show();
        sleep(0.01);
    }
}

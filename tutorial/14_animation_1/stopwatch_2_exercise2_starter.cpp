void small_main()
{
    Window window;
    window.open(640, 480);

    double y = 100;
    double speed = 150;
    StopWatch watch;

    while (window.is_open())
    {
        // Measure dt and move using seconds.

        window.clear(Black);
        window.fill_circle(320, y, 20, Green);
        window.show();
    }
}

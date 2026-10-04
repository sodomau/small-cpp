void small_main()
{
    Window window;
    window.open(640, 480);

    double x = 50;

    while (window.is_open())
    {
        x = x + 2;

        if (x > 640)
            x = 0;

        window.clear(Black);
        window.fill_circle(x, 240, 20, Yellow);
        window.show();
        sleep(0.01);
    }
}

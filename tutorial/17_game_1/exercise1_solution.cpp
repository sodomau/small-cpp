void small_main()
{
    Window window;
    window.open(800, 500);

    double paddle_y = 210;
    StopWatch watch;

    while (window.is_open())
    {
        double dt = watch.elapsed();
        watch.reset();

        if (window.key_down(Key::Up))
            paddle_y = paddle_y - 300 * dt;
        if (window.key_down(Key::Down))
            paddle_y = paddle_y + 300 * dt;

        if (paddle_y < 0) paddle_y = 0;
        if (paddle_y > 420) paddle_y = 420;

        window.clear(Black);
        window.fill_rectangle(30, paddle_y, 15, 80, White);
        window.show();
    }
}

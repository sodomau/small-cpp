int seconds = 0;

void on_second()
{
    seconds = seconds + 1;
}

void small_main()
{
    Window window;
    window.open(500, 250);

    Timer timer;
    timer.start(1.0, on_second);

    while (window.is_open())
    {
        window.clear(Black);
        window.draw_text(30, 80, format("Seconds: ", seconds), White, 28);
        window.show();
    }

    timer.stop();
}

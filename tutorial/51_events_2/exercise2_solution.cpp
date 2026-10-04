int level = 1;

void on_second()
{
    level = level + 1;
}

void small_main()
{
    Window window;
    window.open(500, 300);

    Timer timer;
    timer.start(1.0, on_second);

    while (window.is_open())
    {
        window.set_title("Level ", level);
        window.clear(Black);
        window.show();
    }

    timer.stop();
}

int ticks = 0;

void on_timer()
{
    ticks = ticks + 1;
    print("Tick ", ticks);
}

void small_main()
{
    Timer timer;

    timer.start(1.0, on_timer);
    sleep(3.2);
    timer.stop();
}

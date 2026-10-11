int count = 0;

void on_timer()
{
    count = count + 1;
    print("Count: ", count);
}

void small_main()
{
    Timer timer;
    timer.start(0.5, on_timer);

    sleep(2.2);

    timer.stop();
}

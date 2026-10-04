bool is_ready = false;

void on_ready()
{
    is_ready = true;
}

void small_main()
{
    print("Press ENTER, then wait for the beep.");
    input();

    // Change is_ready later without blocking the program.
    Timer timer;
    timer.start(2.0, on_ready);

    while (!is_ready)
        sleep(0.01);

    timer.stop();
    play_sound(Sound::Coin);

    StopWatch watch;
    input("Press ENTER as fast as you can! ");

    print("Reaction time: ", watch.elapsed(), " seconds");
}

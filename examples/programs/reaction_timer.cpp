bool ready = false;

void OnReady()
{
    ready = true;
}

void SmallMain()
{
    Print("Press ENTER, then wait for the beep.");
    Input();

    // Change ready later without blocking the program.
    Timer timer;
    timer.Start(2.0, OnReady);

    while (!ready)
        Sleep(0.01);

    timer.Stop();
    PlaySound(Sound::Coin);

    StopWatch watch;
    Input("Press ENTER as fast as you can! ");

    Print("Reaction time: ", watch.Elapsed(), " seconds");
}

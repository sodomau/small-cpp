int ticks = 0;

void OnTimer()
{
    ticks = ticks + 1;
    Print("Tick ", ticks);
}

void SmallMain()
{
    Timer timer;

    timer.Start(1.0, OnTimer);
    Print("Running: ", timer.IsRunning());

    Sleep(3.2);

    timer.Stop();
    Print("Running: ", timer.IsRunning());
}

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
    Sleep(3.2);
    timer.Stop();
}

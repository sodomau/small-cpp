int count = 0;

void OnTimer()
{
    count = count + 1;
    Print("Count: ", count);
}

void SmallMain()
{
    Timer timer;
    timer.Start(0.5, OnTimer);

    Sleep(2.2);

    timer.Stop();
}

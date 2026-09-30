void SmallMain()
{
    StopWatch watch;

    Sleep(0.5);
    Print("Elapsed: ", watch.Elapsed());

    watch.Reset();
    Sleep(0.2);
    Print("After reset: ", watch.Elapsed());
}

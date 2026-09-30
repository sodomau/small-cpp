void SmallMain()
{
    StopWatch watch;

    Sleep(1.0);
    Print("About one second: ", watch.Elapsed());

    watch.Reset();
    Sleep(0.5);
    Print("About half a second: ", watch.Elapsed());
}

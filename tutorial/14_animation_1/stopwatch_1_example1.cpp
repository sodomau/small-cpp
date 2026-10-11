void small_main()
{
    StopWatch watch;

    sleep(1.0);
    print("About one second: ", watch.elapsed());

    watch.reset();
    sleep(0.5);
    print("About half a second: ", watch.elapsed());
}

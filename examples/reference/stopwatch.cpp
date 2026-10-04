void small_main()
{
    StopWatch watch;

    sleep(0.5);
    print("Elapsed: ", watch.elapsed());

    watch.reset();
    sleep(0.2);
    print("After reset: ", watch.elapsed());
}

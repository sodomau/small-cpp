void small_main()
{
    int n = 1000;
    int steps = 0;

    while (n > 0)
    {
        n = n / 2;
        steps = steps + 1;
    }

    print(steps);
}

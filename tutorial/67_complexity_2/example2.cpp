void small_main()
{
    int n = 1024;
    int steps = 0;

    while (n > 0)
    {
        print(n);
        n = n / 2;
        steps = steps + 1;
    }

    print("Steps: ", steps);
}

void SmallMain()
{
    int n = 1024;
    int steps = 0;

    while (n > 0)
    {
        Print(n);
        n = n / 2;
        steps = steps + 1;
    }

    Print("Steps: ", steps);
}

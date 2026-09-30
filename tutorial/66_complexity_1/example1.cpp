void SmallMain()
{
    Array<int> sizes = {10, 100, 1000};

    for (int i = 0; i < sizes.Length(); i = i + 1)
    {
        int n = sizes[i];
        int linear = n;
        Print("n = ", n, ", linear worst case = ", linear);
    }
}

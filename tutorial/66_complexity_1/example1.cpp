void small_main()
{
    Array<int> sizes = {10, 100, 1000};

    for (int i = 0; i < sizes.length(); i = i + 1)
    {
        int n = sizes[i];
        int linear = n;
        print("n = ", n, ", linear worst case = ", linear);
    }
}

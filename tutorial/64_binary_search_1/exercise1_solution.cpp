void small_main()
{
    Array<int> numbers = {4, 8, 15, 16, 23, 42};
    int value = 23;
    int index = -1;
    int left = 0;
    int right = numbers.length() - 1;

    while (left <= right)
    {
        int middle = (left + right) / 2;

        if (numbers[middle] == value)
        {
            index = middle;
            break;
        }

        if (value < numbers[middle])
            right = middle - 1;
        else
            left = middle + 1;
    }

    print(index);
}

int binary_search(Array<int> numbers, int value)
{
    int left = 0;
    int right = numbers.length() - 1;

    while (left <= right)
    {
        int middle = (left + right) / 2;

        if (numbers[middle] == value)
            return middle;

        if (value < numbers[middle])
            right = middle - 1;
        else
            left = middle + 1;
    }

    return -1;
}

void small_main()
{
    Array<int> numbers = {1, 3, 5, 7, 9, 11, 13};
    print(binary_search(numbers, 11));
}

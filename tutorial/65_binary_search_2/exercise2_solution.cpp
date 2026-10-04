void small_main()
{
    Array<int> numbers = {1, 3, 5, 7, 9, 11, 13, 15, 17};
    int value = 17;
    int comparisons = 0;
    int left = 0;
    int right = numbers.length() - 1;

    while (left <= right)
    {
        int middle = (left + right) / 2;
        comparisons = comparisons + 1;

        if (numbers[middle] == value)
            break;

        if (value < numbers[middle])
            right = middle - 1;
        else
            left = middle + 1;
    }

    print("Comparisons: ", comparisons);
}

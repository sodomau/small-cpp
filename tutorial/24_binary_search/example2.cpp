void SmallMain()
{
    Array<int> numbers = {2, 5, 8, 12, 16, 23, 38, 56};
    int value = 23;

    int left = 0;
    int right = numbers.Length() - 1;
    int comparisons = 0;

    while (left <= right)
    {
        int middle = (left + right) / 2;
        comparisons = comparisons + 1;
        Print("Checking ", numbers[middle]);

        if (numbers[middle] == value)
            break;

        if (value < numbers[middle])
            right = middle - 1;
        else
            left = middle + 1;
    }

    Print("Comparisons: ", comparisons);
}

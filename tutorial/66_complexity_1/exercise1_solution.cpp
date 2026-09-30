void SmallMain()
{
    Array<int> numbers(20);
    int comparisons = 0;

    for (int i = 0; i < numbers.Length(); i = i + 1)
    {
        comparisons = comparisons + 1;
        if (numbers[i] == 99)
            break;
    }

    Print(comparisons);
}

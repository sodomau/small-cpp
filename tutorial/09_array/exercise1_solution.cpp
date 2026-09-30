void SmallMain()
{
    Array<int> numbers = {2, 4, 6, 8, 10};

    for (int i = 0; i < numbers.Length(); i = i + 1)
    {
        numbers[i] = numbers[i] * 2;
    }

    for (int i = 0; i < numbers.Length(); i = i + 1)
    {
        Print(numbers[i]);
    }
}

void SmallMain()
{
    Array<int> numbers(3);
    for (int i = 0; i < numbers.Length(); i = i + 1)
    {
        numbers[i] = i + 1;
        Print(numbers[i]);
    }
}

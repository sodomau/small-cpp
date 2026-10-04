void small_main()
{
    Array<int> numbers(3);
    for (int i = 0; i < numbers.length(); i = i + 1)
    {
        numbers[i] = i + 1;
        print(numbers[i]);
    }
}

void small_main()
{
    Array<int> numbers(5);
    for (int i = 0; i < numbers.length(); i = i + 1)
    {
        numbers[i] = i + 1;
        print(numbers[i]);
    }
}

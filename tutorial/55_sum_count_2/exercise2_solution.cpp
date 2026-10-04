void small_main()
{
    Array<int> numbers = {-2, 5, 0, 8, -1, 3};
    int count = 0;

    for (int i = 0; i < numbers.length(); i = i + 1)
        if (numbers[i] > 0)
            count = count + 1;

    print(count);
}

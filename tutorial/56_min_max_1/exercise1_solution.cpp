void small_main()
{
    Array<int> numbers = {8, -3, 5, 2, -1};
    int smallest = numbers[0];

    for (int i = 1; i < numbers.length(); i = i + 1)
        if (numbers[i] < smallest)
            smallest = numbers[i];

    print(smallest);
}

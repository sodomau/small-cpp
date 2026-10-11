void small_main()
{
    Array<int> numbers = {3, 7, 2, 9, 4};
    int total = 0;

    for (int i = 0; i < numbers.length(); i = i + 1)
        total = total + numbers[i];

    print("Sum: ", total);
}

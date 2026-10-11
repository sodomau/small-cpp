void small_main()
{
    Array<int> numbers = {10, 20, 30, 40};
    double total = 0;

    for (int i = 0; i < numbers.length(); i = i + 1)
        total = total + numbers[i];

    print("Average: ", total / numbers.length());
}

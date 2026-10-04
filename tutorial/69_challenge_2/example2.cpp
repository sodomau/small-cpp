void small_main()
{
    Array<int> numbers = {4, 9, 2, 9, 7};

    int largest = numbers[0];
    int count_largest = 0;

    for (int i = 0; i < numbers.length(); i = i + 1)
        if (numbers[i] > largest)
            largest = numbers[i];

    for (int i = 0; i < numbers.length(); i = i + 1)
        if (numbers[i] == largest)
            count_largest = count_largest + 1;

    print("Largest: ", largest);
    print("How many: ", count_largest);
}

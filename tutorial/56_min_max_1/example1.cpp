void small_main()
{
    Array<int> numbers = {7, 2, 9, 4, 5};
    int largest = numbers[0];

    for (int i = 1; i < numbers.length(); i = i + 1)
        if (numbers[i] > largest)
            largest = numbers[i];

    print("Largest: ", largest);
}

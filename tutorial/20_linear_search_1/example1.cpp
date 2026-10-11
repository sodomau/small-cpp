int find(Array<int> numbers, int value)
{
    for (int i = 0; i < numbers.length(); i = i + 1)
        if (numbers[i] == value)
            return i;

    return -1;
}

void small_main()
{
    Array<int> numbers = {7, 2, 9, 4, 5};
    print("Index: ", find(numbers, 9));
}

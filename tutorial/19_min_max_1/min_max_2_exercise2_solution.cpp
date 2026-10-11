void small_main()
{
    Array<int> numbers = {4, 11, 6, 20, 9};
    int largest_index = 0;

    for (int i = 1; i < numbers.length(); i = i + 1)
        if (numbers[i] > numbers[largest_index])
            largest_index = i;

    print("Value: ", numbers[largest_index]);
    print("Index: ", largest_index);
}

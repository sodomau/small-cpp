void small_main()
{
    Array<int> numbers = {7, 2, 9, 1, 5};
    int smallest_index = 0;

    for (int i = 1; i < numbers.length(); i = i + 1)
        if (numbers[i] < numbers[smallest_index])
            smallest_index = i;

    print("Smallest: ", numbers[smallest_index]);
    print("Index: ", smallest_index);
}

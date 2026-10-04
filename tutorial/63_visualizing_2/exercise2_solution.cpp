void small_main()
{
    Array<int> numbers = {7, 2, 9, 4, 5};
    int swaps = 0;

    for (int i = 0; i < numbers.length(); i = i + 1)
    {
        int smallest = i;

        for (int j = i + 1; j < numbers.length(); j = j + 1)
            if (numbers[j] < numbers[smallest])
                smallest = j;

        if (smallest != i)
        {
            int temp = numbers[i];
            numbers[i] = numbers[smallest];
            numbers[smallest] = temp;
            swaps = swaps + 1;
        }
    }

    print("Swaps: ", swaps);
}

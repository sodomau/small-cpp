void small_main()
{
    Array<int> numbers = {10, 3, 8, 1, 6};

    for (int i = 0; i < numbers.length(); i = i + 1)
    {
        int largest = i;
        for (int j = i + 1; j < numbers.length(); j = j + 1)
            if (numbers[j] > numbers[largest])
                largest = j;

        int temp = numbers[i];
        numbers[i] = numbers[largest];
        numbers[largest] = temp;
    }

    for (int i = 0; i < numbers.length(); i = i + 1)
        print(numbers[i]);
}

void SmallMain()
{
    Array<int> numbers = {7, 2, 9, 4, 5};

    for (int i = 0; i < numbers.Length(); i = i + 1)
    {
        int smallest = i;

        for (int j = i + 1; j < numbers.Length(); j = j + 1)
            if (numbers[j] < numbers[smallest])
                smallest = j;

        int temp = numbers[i];
        numbers[i] = numbers[smallest];
        numbers[smallest] = temp;
    }

    for (int i = 0; i < numbers.Length(); i = i + 1)
        Print(numbers[i]);
}

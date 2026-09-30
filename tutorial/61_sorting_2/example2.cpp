void SmallMain()
{
    Array<int> numbers = {7, 2, 9, 4, 5};

    for (int i = 0; i < numbers.Length(); i = i + 1)
    {
        int largest = i;

        for (int j = i + 1; j < numbers.Length(); j = j + 1)
            if (numbers[j] > numbers[largest])
                largest = j;

        int temp = numbers[i];
        numbers[i] = numbers[largest];
        numbers[largest] = temp;
    }

    for (int i = 0; i < numbers.Length(); i = i + 1)
        Print(numbers[i]);
}

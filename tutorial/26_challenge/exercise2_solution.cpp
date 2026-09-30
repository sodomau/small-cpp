void SmallMain()
{
    Array<int> numbers = {5, 9, 2, 9, 9, 4};
    int largest = numbers[0];

    for (int i = 1; i < numbers.Length(); i = i + 1)
        if (numbers[i] > largest)
            largest = numbers[i];

    int count = 0;

    for (int i = 0; i < numbers.Length(); i = i + 1)
        if (numbers[i] == largest)
            count = count + 1;

    Print("Largest: ", largest);
    Print("Count: ", count);
}

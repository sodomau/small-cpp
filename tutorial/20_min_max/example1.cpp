void SmallMain()
{
    Array<int> numbers = {7, 2, 9, 4, 5};
    int largest = numbers[0];

    for (int i = 1; i < numbers.Length(); i = i + 1)
        if (numbers[i] > largest)
            largest = numbers[i];

    Print("Largest: ", largest);
}

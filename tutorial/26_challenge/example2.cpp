void SmallMain()
{
    Array<int> numbers = {4, 9, 2, 9, 7};

    int largest = numbers[0];
    int countLargest = 0;

    for (int i = 0; i < numbers.Length(); i = i + 1)
        if (numbers[i] > largest)
            largest = numbers[i];

    for (int i = 0; i < numbers.Length(); i = i + 1)
        if (numbers[i] == largest)
            countLargest = countLargest + 1;

    Print("Largest: ", largest);
    Print("How many: ", countLargest);
}

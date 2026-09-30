void SmallMain()
{
    Array<int> numbers = {7, 2, 9, 1, 5};
    int smallestIndex = 0;

    for (int i = 1; i < numbers.Length(); i = i + 1)
        if (numbers[i] < numbers[smallestIndex])
            smallestIndex = i;

    Print("Smallest: ", numbers[smallestIndex]);
    Print("Index: ", smallestIndex);
}

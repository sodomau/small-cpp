void SmallMain()
{
    Array<int> numbers = {4, 11, 6, 20, 9};
    int largestIndex = 0;

    for (int i = 1; i < numbers.Length(); i = i + 1)
        if (numbers[i] > numbers[largestIndex])
            largestIndex = i;

    Print("Value: ", numbers[largestIndex]);
    Print("Index: ", largestIndex);
}

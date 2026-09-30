int FindLargest(Array<int> numbers)
{
    int largest = numbers[0];

    for (int i = 1; i < numbers.Length(); i = i + 1)
        if (numbers[i] > largest)
            largest = numbers[i];

    return largest;
}

void SmallMain()
{
    Array<int> numbers = {4, 12, 3, 9};
    Print(FindLargest(numbers));
}

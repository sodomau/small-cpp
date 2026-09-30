void SmallMain()
{
    Array<int> numbers = {3, 7, 2, 7, 5, 7};
    int value = 7;
    int index = -1;

    for (int i = 0; i < numbers.Length(); i = i + 1)
        if (numbers[i] == value)
            index = i;

    Print(index);
}

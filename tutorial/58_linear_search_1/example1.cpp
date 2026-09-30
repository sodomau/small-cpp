int Find(Array<int> numbers, int value)
{
    for (int i = 0; i < numbers.Length(); i = i + 1)
        if (numbers[i] == value)
            return i;

    return -1;
}

void SmallMain()
{
    Array<int> numbers = {7, 2, 9, 4, 5};
    Print("Index: ", Find(numbers, 9));
}

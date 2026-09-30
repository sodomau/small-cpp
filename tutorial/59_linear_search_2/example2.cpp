void SmallMain()
{
    Array<int> numbers = {7, 2, 9, 4, 5};
    int value = InputInt("Find: ");
    int index = -1;

    for (int i = 0; i < numbers.Length(); i = i + 1)
        if (numbers[i] == value)
        {
            index = i;
            break;
        }

    if (index == -1)
        Print("Not found");
    else
        Print("Found at ", index);
}

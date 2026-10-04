void small_main()
{
    Array<int> numbers = {7, 2, 9, 4, 5};
    int value = input_int("Find: ");
    int index = -1;

    for (int i = 0; i < numbers.length(); i = i + 1)
        if (numbers[i] == value)
        {
            index = i;
            break;
        }

    if (index == -1)
        print("Not found");
    else
        print("Found at ", index);
}

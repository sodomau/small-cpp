void SmallMain()
{
    Array<int> numbers = {3, 7, 2, 9, 4};
    int total = 0;

    for (int i = 0; i < numbers.Length(); i = i + 1)
        total = total + numbers[i];

    Print("Sum: ", total);
}

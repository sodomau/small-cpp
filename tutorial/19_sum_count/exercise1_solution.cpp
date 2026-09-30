void SmallMain()
{
    Array<int> numbers = {10, 20, 30, 40};
    double total = 0;

    for (int i = 0; i < numbers.Length(); i = i + 1)
        total = total + numbers[i];

    Print("Average: ", total / numbers.Length());
}

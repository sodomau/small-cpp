int Sum(Array<int> numbers)
{
    int total = 0;

    for (int i = 0; i < numbers.Length(); i = i + 1)
    {
        total = total + numbers[i];
    }

    return total;
}

void SmallMain()
{
    Array<int> numbers = {3, 7, 2, 9, 4};

    numbers[2] = 10;

    Print("Third: ", numbers[2]);
    Print("Sum: ", Sum(numbers));
}

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
    Array<int> numbers = {5, 10, 15, 20};
    Print(Sum(numbers));
}

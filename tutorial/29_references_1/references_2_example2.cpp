int sum(const Array<int>& numbers)
{
    int total = 0;

    for (int i = 0; i < numbers.length(); i = i + 1)
        total = total + numbers[i];

    return total;
}

void small_main()
{
    Array<int> numbers = {3, 7, 2, 9, 4};

    print("Sum: ", sum(numbers));
}

int find_largest(const Array<int>& numbers)
{
    int largest = numbers[0];

    for (int i = 1; i < numbers.length(); i = i + 1)
        if (numbers[i] > largest)
            largest = numbers[i];

    return largest;
}

void small_main()
{
    Array<int> numbers = {4, 12, 3, 9};
    print(find_largest(numbers));
}

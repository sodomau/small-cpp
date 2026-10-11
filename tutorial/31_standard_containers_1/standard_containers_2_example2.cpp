int sum(const std::vector<int>& numbers)
{
    int total = 0;

    for (int value : numbers)
        total = total + value;

    return total;
}

void small_main()
{
    std::vector<int> numbers = {10, 20, 30};
    numbers.push_back(40);

    print("Sum: ", sum(numbers));
}

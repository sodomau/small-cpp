void small_main()
{
    std::vector<int> numbers = {5, 10};
    numbers.push_back(15);

    for (int value : numbers)
        print(value);
}

int count_even(Array<int> numbers)
{
    int count = 0;

    for (int i = 0; i < numbers.length(); i = i + 1)
        if (numbers[i] % 2 == 0)
            count = count + 1;

    return count;
}

void small_main()
{
    Array<int> numbers = {3, 8, 4, 7, 10};
    print("Even: ", count_even(numbers));
}

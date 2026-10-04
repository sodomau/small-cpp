void small_main()
{
    Array<int> numbers = {8, 3, 12, 5, 10};

    int smallest = numbers[0];
    int second = numbers[1];

    if (second < smallest)
    {
        int temp = smallest;
        smallest = second;
        second = temp;
    }

    for (int i = 2; i < numbers.length(); i = i + 1)
    {
        if (numbers[i] < smallest)
        {
            second = smallest;
            smallest = numbers[i];
        }
        else if (numbers[i] < second)
        {
            second = numbers[i];
        }
    }

    print(second);
}

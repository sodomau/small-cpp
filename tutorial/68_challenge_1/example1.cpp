void SmallMain()
{
    Array<int> numbers = {8, 3, 12, 5, 10};

    int largest = numbers[0];
    int second = numbers[1];

    if (second > largest)
    {
        int temp = largest;
        largest = second;
        second = temp;
    }

    for (int i = 2; i < numbers.Length(); i = i + 1)
    {
        if (numbers[i] > largest)
        {
            second = largest;
            largest = numbers[i];
        }
        else if (numbers[i] > second)
        {
            second = numbers[i];
        }
    }

    Print("Second largest: ", second);
}

void small_main()
{
    Window window;
    window.open(450, 450);

    Array<int> numbers = {7, 2, 9, 4, 5};

    for (int i = 0; i < numbers.length(); i = i + 1)
    {
        int smallest = i;

        for (int j = i + 1; j < numbers.length(); j = j + 1)
            if (numbers[j] < numbers[smallest])
                smallest = j;

        int temp = numbers[i];
        numbers[i] = numbers[smallest];
        numbers[smallest] = temp;

        window.clear(White);

        for (int j = 0; j < numbers.length(); j = j + 1)
        {
            double height = numbers[j] * 30;
            Color color = Blue;
            if (j == i)
                color = Red;

            window.fill_rectangle(40 + j * 70, 420 - height, 50, height, color);
        }

        window.show();
        sleep(0.5);
    }

    while (window.is_open())
        window.show();
}

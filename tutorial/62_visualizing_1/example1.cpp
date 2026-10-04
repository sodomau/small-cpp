void small_main()
{
    Window window;
    window.open(450, 450);

    Array<int> numbers = {7, 2, 9, 4, 5};

    window.clear(White);

    for (int i = 0; i < numbers.length(); i = i + 1)
    {
        double height = numbers[i] * 30;
        window.fill_rectangle(40 + i * 70, 420 - height, 50, height, Blue);
    }

    window.show();

    while (window.is_open())
        window.show();
}

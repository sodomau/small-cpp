void SmallMain()
{
    Window window;
    window.Open(450, 450);

    Array<int> numbers = {7, 2, 9, 4, 5};
    int current = 2;

    window.Clear(White);

    for (int i = 0; i < numbers.Length(); i = i + 1)
    {
        double height = numbers[i] * 30;
        Color color = Blue;

        if (i == current)
            color = Red;

        window.FillRectangle(40 + i * 70, 420 - height, 50, height, color);
    }

    window.Show();

    while (window.IsOpen())
        window.Show();
}

void SmallMain()
{
    Window window;
    window.Open(640, 480);

    double x = 50;

    while (window.IsOpen())
    {
        x = x + 2;

        if (x > 640)
            x = 0;

        window.Clear(Black);
        window.FillCircle(x, 240, 20, Yellow);
        window.Show();
        Sleep(0.01);
    }
}

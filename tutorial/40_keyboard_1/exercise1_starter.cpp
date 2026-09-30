void SmallMain()
{
    Window window;
    window.Open(640, 480);

    double x = 320;
    double y = 240;

    while (window.IsOpen())
    {
        // Move with W, A, S, D.

        window.Clear(Black);
        window.FillCircle(x, y, 20, Cyan);
        window.Show();
    }
}

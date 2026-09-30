void SmallMain()
{
    Window window;
    window.Open(800, 500);

    double paddleY = 210;
    StopWatch watch;

    while (window.IsOpen())
    {
        double dt = watch.Elapsed();
        watch.Reset();

        if (window.KeyDown(Key::Up))
            paddleY = paddleY - 300 * dt;
        if (window.KeyDown(Key::Down))
            paddleY = paddleY + 300 * dt;

        // Keep paddleY between 0 and 420.

        window.Clear(Black);
        window.FillRectangle(30, paddleY, 15, 80, White);
        window.Show();
    }
}

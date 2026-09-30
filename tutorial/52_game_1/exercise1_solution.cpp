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

        if (paddleY < 0) paddleY = 0;
        if (paddleY > 420) paddleY = 420;

        window.Clear(Black);
        window.FillRectangle(30, paddleY, 15, 80, White);
        window.Show();
    }
}

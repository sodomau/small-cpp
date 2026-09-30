void SmallMain()
{
    Window window;
    window.Open(640, 480);

    int score = 0;
    double ballX = 320;
    double ballY = 100;
    double ballVY = 180;
    StopWatch watch;

    while (window.IsOpen())
    {
        double dt = watch.Elapsed();
        watch.Reset();

        ballY = ballY + ballVY * dt;

        if (ballY > 420)
        {
            ballY = 420;
            ballVY = -ballVY;
            score = score + 1;
            PlaySound(Sound::Hit);
        }

        if (ballY < 20)
        {
            ballY = 20;
            ballVY = -ballVY;
        }

        window.SetTitle("Score: ", score);

        window.Clear(Black);
        window.FillRectangle(250, 450, 140, 10, White);
        window.FillCircle(ballX, ballY, 20, Yellow);
        window.Show();
    }
}

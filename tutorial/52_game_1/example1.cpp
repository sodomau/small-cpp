void SmallMain()
{
    Window window;
    window.SetTitle("Mini Pong");
    window.Open(800, 500);

    double paddleY = 210;
    double ballX = 400;
    double ballY = 250;
    double ballVX = 260;
    double ballVY = 180;

    StopWatch watch;

    while (window.IsOpen())
    {
        double dt = watch.Elapsed();
        watch.Reset();

        if (window.KeyDown(Key::Up))
            paddleY = paddleY - 300 * dt;
        if (window.KeyDown(Key::Down))
            paddleY = paddleY + 300 * dt;

        ballX = ballX + ballVX * dt;
        ballY = ballY + ballVY * dt;

        if (ballY < 10)
        {
            ballY = 10;
            ballVY = -ballVY;
        }

        if (ballY > 490)
        {
            ballY = 490;
            ballVY = -ballVY;
        }

        if (ballX < 50 && ballX > 30 &&
            ballY > paddleY && ballY < paddleY + 80)
        {
            ballX = 50;
            ballVX = -ballVX;
            PlaySound(Sound::Hit);
        }

        if (ballX > 790)
        {
            ballX = 790;
            ballVX = -ballVX;
        }

        if (ballX < 0)
        {
            ballX = 400;
            ballY = 250;
            ballVX = 260;
            PlaySound(Sound::Lose);
        }

        window.Clear(Black);
        window.FillRectangle(30, paddleY, 15, 80, White);
        window.FillCircle(ballX, ballY, 10, Yellow);
        window.Show();
    }
}

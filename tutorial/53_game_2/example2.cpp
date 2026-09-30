void SmallMain()
{
    Window window;
    window.SetTitle("Catch the Ball");
    window.Open(640, 480);

    double playerX = 320;
    double ballX = 100;
    double ballY = 80;
    double ballVX = 180;
    double ballVY = 140;
    int score = 0;

    StopWatch watch;

    while (window.IsOpen())
    {
        double dt = watch.Elapsed();
        watch.Reset();

        if (window.KeyDown(Key::Left)) playerX = playerX - 250 * dt;
        if (window.KeyDown(Key::Right)) playerX = playerX + 250 * dt;

        ballX = ballX + ballVX * dt;
        ballY = ballY + ballVY * dt;

        if (ballX < 15)
        {
            ballX = 15;
            ballVX = -ballVX;
        }

        if (ballX > 625)
        {
            ballX = 625;
            ballVX = -ballVX;
        }

        if (ballY < 15)
        {
            ballY = 15;
            ballVY = -ballVY;
        }

        if (ballY > 430 && ballY < 460 &&
            ballX > playerX - 60 && ballX < playerX + 60)
        {
            ballY = 430;
            ballVY = -ballVY;
            score = score + 1;
            PlaySound(Sound::Coin);
        }

        if (ballY > 500)
        {
            ballX = 100;
            ballY = 80;
        }

        window.SetTitle("Score: ", score);
        window.Clear(Black);
        window.FillRectangle(playerX - 60, 450, 120, 12, White);
        window.FillCircle(ballX, ballY, 15, Cyan);
        window.Show();
    }
}

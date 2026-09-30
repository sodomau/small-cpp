void SmallMain()
{
    Window window;
    window.Open(640, 480);
    int score = 0;
    double paddleX = 320;
    double ballX = 320;
    double ballY = 100;
    double ballVY = 180;
    StopWatch watch;
    while (window.IsOpen())
    {
        double dt = watch.Elapsed();
        watch.Reset();
        if (window.KeyDown(Key::Left)) { paddleX = paddleX - 250 * dt; }
        if (window.KeyDown(Key::Right)) { paddleX = paddleX + 250 * dt; }
        if (paddleX < 70) { paddleX = 70; }
        if (paddleX > 570) { paddleX = 570; }
        double previousY = ballY;
        ballY = ballY + ballVY * dt;
        if (ballVY > 0 && previousY <= 430 && ballY >= 430 &&
            ballX >= paddleX - 70 && ballX <= paddleX + 70)
        {
            ballY = 430;
            ballVY = -ballVY;
            // Increase score only on a paddle hit.
            PlaySound(Sound::Hit);
        }
        if (ballY < 20) { ballY = 20; ballVY = -ballVY; }
        if (ballY > 500) { ballY = 100; ballVY = 180; }
        // Show score in the window title.
        window.Clear(Black);
        window.FillRectangle(paddleX - 70, 450, 140, 10, White);
        window.FillCircle(ballX, ballY, 20, Yellow);
        window.Show();
    }
}

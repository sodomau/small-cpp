void small_main()
{
    Window window;
    window.open(640, 480);
    int score = 0;
    double paddle_x = 320;
    double ball_x = 320;
    double ball_y = 100;
    double ball_vy = 180;
    StopWatch watch;
    while (window.is_open())
    {
        double dt = watch.elapsed();
        watch.reset();
        if (window.key_down(Key::Left)) { paddle_x = paddle_x - 250 * dt; }
        if (window.key_down(Key::Right)) { paddle_x = paddle_x + 250 * dt; }
        if (paddle_x < 70) { paddle_x = 70; }
        if (paddle_x > 570) { paddle_x = 570; }
        double previous_y = ball_y;
        ball_y = ball_y + ball_vy * dt;
        if (ball_vy > 0 && previous_y <= 430 && ball_y >= 430 &&
            ball_x >= paddle_x - 70 && ball_x <= paddle_x + 70)
        {
            ball_y = 430;
            ball_vy = -ball_vy;
            score = score + 1;
            play_sound(Sound::Hit);
        }
        if (ball_y < 20) { ball_y = 20; ball_vy = -ball_vy; }
        if (ball_y > 500) { ball_y = 100; ball_vy = 180; }
        window.set_title("Score: ", score);
        window.clear(Black);
        window.fill_rectangle(paddle_x - 70, 450, 140, 10, White);
        window.fill_circle(ball_x, ball_y, 20, Yellow);
        window.show();
    }
}

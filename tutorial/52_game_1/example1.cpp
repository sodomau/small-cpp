void small_main()
{
    Window window;
    window.set_title("Mini Pong");
    window.open(800, 500);

    double paddle_y = 210;
    double ball_x = 400;
    double ball_y = 250;
    double ball_vx = 260;
    double ball_vy = 180;

    StopWatch watch;

    while (window.is_open())
    {
        double dt = watch.elapsed();
        watch.reset();

        if (window.key_down(Key::Up))
            paddle_y = paddle_y - 300 * dt;
        if (window.key_down(Key::Down))
            paddle_y = paddle_y + 300 * dt;

        ball_x = ball_x + ball_vx * dt;
        ball_y = ball_y + ball_vy * dt;

        if (ball_y < 10)
        {
            ball_y = 10;
            ball_vy = -ball_vy;
        }

        if (ball_y > 490)
        {
            ball_y = 490;
            ball_vy = -ball_vy;
        }

        if (ball_x < 50 && ball_x > 30 &&
            ball_y > paddle_y && ball_y < paddle_y + 80)
        {
            ball_x = 50;
            ball_vx = -ball_vx;
            play_sound(Sound::Hit);
        }

        if (ball_x > 790)
        {
            ball_x = 790;
            ball_vx = -ball_vx;
        }

        if (ball_x < 0)
        {
            ball_x = 400;
            ball_y = 250;
            ball_vx = 260;
            play_sound(Sound::Lose);
        }

        window.clear(Black);
        window.fill_rectangle(30, paddle_y, 15, 80, White);
        window.fill_circle(ball_x, ball_y, 10, Yellow);
        window.show();
    }
}

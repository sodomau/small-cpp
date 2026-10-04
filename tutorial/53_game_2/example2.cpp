void small_main()
{
    Window window;
    window.set_title("Catch the Ball");
    window.open(640, 480);

    double player_x = 320;
    double ball_x = 100;
    double ball_y = 80;
    double ball_vx = 180;
    double ball_vy = 140;
    int score = 0;

    StopWatch watch;

    while (window.is_open())
    {
        double dt = watch.elapsed();
        watch.reset();

        if (window.key_down(Key::Left)) player_x = player_x - 250 * dt;
        if (window.key_down(Key::Right)) player_x = player_x + 250 * dt;

        ball_x = ball_x + ball_vx * dt;
        ball_y = ball_y + ball_vy * dt;

        if (ball_x < 15)
        {
            ball_x = 15;
            ball_vx = -ball_vx;
        }

        if (ball_x > 625)
        {
            ball_x = 625;
            ball_vx = -ball_vx;
        }

        if (ball_y < 15)
        {
            ball_y = 15;
            ball_vy = -ball_vy;
        }

        if (ball_y > 430 && ball_y < 460 &&
            ball_x > player_x - 60 && ball_x < player_x + 60)
        {
            ball_y = 430;
            ball_vy = -ball_vy;
            score = score + 1;
            play_sound(Sound::Coin);
        }

        if (ball_y > 500)
        {
            ball_x = 100;
            ball_y = 80;
        }

        window.set_title("Score: ", score);
        window.clear(Black);
        window.fill_rectangle(player_x - 60, 450, 120, 12, White);
        window.fill_circle(ball_x, ball_y, 15, Cyan);
        window.show();
    }
}

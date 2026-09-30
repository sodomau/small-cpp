int seconds = 0;

void OnSecond()
{
    seconds = seconds + 1;
}

void SmallMain()
{
    Window window;
    window.Open(500, 250);

    Timer timer;
    timer.Start(1.0, OnSecond);

    while (window.IsOpen())
    {
        window.Clear(Black);
        window.DrawText(30, 80, Format("Seconds: ", seconds), White, 28);
        window.Show();
    }

    timer.Stop();
}

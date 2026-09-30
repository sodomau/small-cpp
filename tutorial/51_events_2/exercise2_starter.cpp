int level = 1;

void OnSecond()
{
    // Increase level.
}

void SmallMain()
{
    Window window;
    window.Open(500, 300);

    Timer timer;
    timer.Start(1.0, OnSecond);

    while (window.IsOpen())
    {
        // Show level in the title.
        window.Clear(Black);
        window.Show();
    }

    timer.Stop();
}

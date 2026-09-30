int level = 1;

void OnSecond()
{
    level = level + 1;
}

void SmallMain()
{
    Window window;
    window.Open(500, 300);

    Timer timer;
    timer.Start(1.0, OnSecond);

    while (window.IsOpen())
    {
        window.SetTitle("Level ", level);
        window.Clear(Black);
        window.Show();
    }

    timer.Stop();
}

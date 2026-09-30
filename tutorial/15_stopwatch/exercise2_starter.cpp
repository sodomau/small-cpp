void SmallMain()
{
    Window window;
    window.Open(640, 480);

    double y = 100;
    double speed = 150;
    StopWatch watch;

    while (window.IsOpen())
    {
        // Measure dt and move using seconds.

        window.Clear(Black);
        window.FillCircle(320, y, 20, Green);
        window.Show();
    }
}

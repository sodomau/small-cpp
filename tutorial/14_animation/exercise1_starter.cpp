void SmallMain()
{
    Window window;
    window.Open(640, 480);

    double y = 100;
    double speed = 3;

    while (window.IsOpen())
    {
        // Update y and bounce.

        window.Clear(Black);
        window.FillCircle(320, y, 20, Green);
        window.Show();
        Sleep(0.01);
    }
}

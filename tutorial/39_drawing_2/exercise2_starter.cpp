void SmallMain()
{
    Window window;
    window.Open(500, 500);

    window.Clear(White);

    // Draw your face here.

    window.Show();
    while (window.IsOpen())
        window.Show();
}

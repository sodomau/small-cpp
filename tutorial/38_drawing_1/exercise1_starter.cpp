void SmallMain()
{
    Window window;
    window.Open(300, 500);

    window.Clear(White);

    // Draw a traffic light here.

    window.Show();
    while (window.IsOpen())
        window.Show();
}

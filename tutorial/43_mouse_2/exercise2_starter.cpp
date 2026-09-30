void SmallMain()
{
    Window window;
    window.Open(640, 480);

    while (window.IsOpen())
    {
        window.Clear(White);

        // Left = red, Right = blue.

        window.Show();
    }
}

void SmallMain()
{
    Window window;
    window.Open(320, 240);

    Print(window.Width(), " x ", window.Height());

    while (window.IsOpen())
        window.Show();
}

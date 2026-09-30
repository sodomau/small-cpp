void SmallMain()
{
    Window window;

    window.SetTitle("Small Window");
    window.Open(400, 300);

    Print("Size: ", window.Width(), " x ", window.Height());

    while (window.IsOpen())
    {
        window.Show();
    }
}

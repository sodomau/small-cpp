void SmallMain()
{
    Window window;
    window.SetTitle("My First Window");
    window.Open(640, 480);

    while (window.IsOpen())
    {
        window.Show();
    }
}

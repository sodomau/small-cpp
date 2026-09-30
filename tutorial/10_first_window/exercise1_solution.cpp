void SmallMain()
{
    Window window;
    window.SetTitle("Alex");
    window.Open(500, 300);

    while (window.IsOpen())
        window.Show();
}

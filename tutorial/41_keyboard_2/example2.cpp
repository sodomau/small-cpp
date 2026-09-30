void SmallMain()
{
    Window window;
    window.Open(640, 480);

    bool red = true;

    while (window.IsOpen())
    {
        if (window.KeyPressed(Key::Space))
            red = !red;

        window.Clear(Black);

        if (red)
            window.FillCircle(320, 240, 60, Red);
        else
            window.FillCircle(320, 240, 60, Blue);

        window.Show();
    }
}

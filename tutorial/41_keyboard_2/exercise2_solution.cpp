void SmallMain()
{
    Window window;
    window.Open(640, 480);

    bool big = false;

    while (window.IsOpen())
    {
        if (window.KeyPressed(Key::Space))
            big = !big;

        window.Clear(Black);

        if (big)
            window.FillCircle(320, 240, 60, Yellow);
        else
            window.FillCircle(320, 240, 20, Yellow);

        window.Show();
    }
}

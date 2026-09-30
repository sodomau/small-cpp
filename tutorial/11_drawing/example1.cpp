void SmallMain()
{
    Window window;
    window.Open(640, 480);

    window.Clear(White);
    window.FillCircle(320, 240, 80, Yellow);
    window.DrawCircle(290, 220, 10, Black);
    window.DrawCircle(350, 220, 10, Black);
    window.DrawLine(285, 275, 355, 275, Black);
    window.Show();

    while (window.IsOpen())
        window.Show();
}

void SmallMain()
{
    Window window;
    window.Open(640, 480);

    Color orange = RGB(255, 140, 0);

    window.Clear(White);
    window.FillRectangle(60, 80, 180, 120, orange);
    window.DrawRectangle(60, 80, 180, 120, Black);
    window.DrawText(80, 110, "Small C++", Blue, 24);
    window.Show();

    while (window.IsOpen())
        window.Show();
}

void SmallMain()
{
    Window window;
    window.Open(640, 480);

    Color orange = RGB(255, 140, 0);

    window.Clear(White);
    window.SetPixel(20, 20, Black);
    window.DrawLine(40, 40, 180, 80, Red);
    window.DrawRectangle(40, 110, 120, 70, Blue);
    window.FillRectangle(330, 225, 30, 30, orange);
    window.FillRectangle(190, 110, 120, 70, Cyan);
    window.DrawCircle(100, 270, 50, Green);
    window.FillCircle(240, 270, 50, Yellow);
    window.DrawText(330, 80, "Small C++");
    window.DrawText(330, 120, "Colored text", Magenta, 24);

    // The built-in colors.
    window.FillRectangle(330, 180, 30, 30, Black);
    window.FillRectangle(365, 180, 30, 30, White);
    window.FillRectangle(400, 180, 30, 30, Red);
    window.FillRectangle(435, 180, 30, 30, Green);
    window.FillRectangle(470, 180, 30, 30, Blue);
    window.FillRectangle(505, 180, 30, 30, Yellow);
    window.FillRectangle(540, 180, 30, 30, Cyan);
    window.FillRectangle(575, 180, 30, 30, Magenta);
    window.FillRectangle(610, 180, 30, 30, Gray);

    window.Show();

    Print("Window size: ", window.Width(), " x ", window.Height());

    while (window.IsOpen())
        window.Show();
}

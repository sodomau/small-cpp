void SmallMain()
{
    Window window;
    window.Open(300, 500);

    window.Clear(White);
    window.FillRectangle(75, 30, 150, 420, Gray);
    window.FillCircle(150, 110, 50, Red);
    window.FillCircle(150, 240, 50, Yellow);
    window.FillCircle(150, 370, 50, Green);
    window.Show();

    while (window.IsOpen())
        window.Show();
}

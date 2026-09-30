void SmallMain()
{
    Window window;
    window.Open(500, 500);

    window.Clear(White);
    window.FillCircle(250, 250, 160, Yellow);
    window.FillCircle(195, 210, 18, Black);
    window.FillCircle(305, 210, 18, Black);
    window.DrawLine(190, 315, 310, 315, Black);
    window.Show();

    while (window.IsOpen())
        window.Show();
}

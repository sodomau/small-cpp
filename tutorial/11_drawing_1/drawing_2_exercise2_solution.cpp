void small_main()
{
    Window window;
    window.open(500, 500);

    window.clear(White);
    window.fill_circle(250, 250, 160, Yellow);
    window.fill_circle(195, 210, 18, Black);
    window.fill_circle(305, 210, 18, Black);
    window.draw_line(190, 315, 310, 315, Black);
    window.show();

    while (window.is_open())
        window.show();
}

void small_main()
{
    Window window;
    window.open(640, 480);

    window.clear(White);
    window.fill_circle(320, 240, 80, Yellow);
    window.draw_circle(290, 220, 10, Black);
    window.draw_circle(350, 220, 10, Black);
    window.draw_line(285, 275, 355, 275, Black);
    window.show();

    while (window.is_open())
        window.show();
}

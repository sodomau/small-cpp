void small_main()
{
    Window window;
    window.open(640, 480);

    Color orange = rgb(255, 140, 0);

    window.clear(White);
    window.set_pixel(20, 20, Black);
    window.draw_line(40, 40, 180, 80, Red);
    window.draw_rectangle(40, 110, 120, 70, Blue);
    window.fill_rectangle(330, 225, 30, 30, orange);
    window.fill_rectangle(190, 110, 120, 70, Cyan);
    window.draw_circle(100, 270, 50, Green);
    window.fill_circle(240, 270, 50, Yellow);
    window.draw_text(330, 80, "Small C++");
    window.draw_text(330, 120, "Colored text", Magenta, 24);

    // The built-in colors.
    window.fill_rectangle(330, 180, 30, 30, Black);
    window.fill_rectangle(365, 180, 30, 30, White);
    window.fill_rectangle(400, 180, 30, 30, Red);
    window.fill_rectangle(435, 180, 30, 30, Green);
    window.fill_rectangle(470, 180, 30, 30, Blue);
    window.fill_rectangle(505, 180, 30, 30, Yellow);
    window.fill_rectangle(540, 180, 30, 30, Cyan);
    window.fill_rectangle(575, 180, 30, 30, Magenta);
    window.fill_rectangle(610, 180, 30, 30, Gray);

    window.show();

    print("Window size: ", window.width(), " x ", window.height());

    while (window.is_open())
        window.show();
}

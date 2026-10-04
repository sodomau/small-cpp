void small_main()
{
    Window window;
    window.open(640, 480);

    Color orange = rgb(255, 140, 0);

    window.clear(White);
    window.fill_rectangle(60, 80, 180, 120, orange);
    window.draw_rectangle(60, 80, 180, 120, Black);
    window.draw_text(80, 110, "Small C++", Blue, 24);
    window.show();

    while (window.is_open())
        window.show();
}

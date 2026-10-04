void small_main()
{
    Window window;
    window.open(300, 500);

    window.clear(White);
    window.fill_rectangle(75, 30, 150, 420, Gray);
    window.fill_circle(150, 110, 50, Red);
    window.fill_circle(150, 240, 50, Yellow);
    window.fill_circle(150, 370, 50, Green);
    window.show();

    while (window.is_open())
        window.show();
}

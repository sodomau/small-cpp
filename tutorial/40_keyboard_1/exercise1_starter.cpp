void small_main()
{
    Window window;
    window.open(640, 480);

    double x = 320;
    double y = 240;

    while (window.is_open())
    {
        // Move with W, A, S, D.

        window.clear(Black);
        window.fill_circle(x, y, 20, Cyan);
        window.show();
    }
}

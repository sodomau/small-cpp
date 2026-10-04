void small_main()
{
    Window window;
    window.set_title("Alex");
    window.open(500, 300);

    while (window.is_open())
        window.show();
}

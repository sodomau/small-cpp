void small_main()
{
    Window window;
    window.open(320, 240);

    print(window.width(), " x ", window.height());

    while (window.is_open())
        window.show();
}

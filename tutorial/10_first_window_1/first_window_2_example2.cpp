void small_main()
{
    Window window;

    window.set_title("Small Window");
    window.open(400, 300);

    print("Size: ", window.width(), " x ", window.height());

    while (window.is_open())
    {
        window.show();
    }
}

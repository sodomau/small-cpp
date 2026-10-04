void small_main()
{
    Window window;
    window.set_title("My First Window");
    window.open(640, 480);

    while (window.is_open())
    {
        window.show();
    }
}

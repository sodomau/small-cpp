void small_main()
{
    Window window;

    print("Default title: ", window.title());

    window.set_title("Window Example");
    print("Title before Open: ", window.title());

    window.open(400, 200);

    print("Width: ", window.width());
    print("Height: ", window.height());
    print("Open: ", window.is_open());

    window.clear(Black);
    window.draw_text(20, 20, "Title changes in one second.", White, 16);
    window.show();

    sleep(1.0);
    window.set_title("Level ", 2, " - Score: ", 100);

    sleep(1.0);
    window.close();

    print("Open: ", window.is_open());
    print("Title after Close: ", window.title());
}

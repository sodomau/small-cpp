void small_main()
{
    Window window;
    window.open(640, 480);

    while (window.is_open())
    {
        if (window.key_pressed(Key::Space)) print("Space pressed");
        if (window.key_released(Key::Enter)) print("Enter released");
        if (window.key_down(Key::Left)) print("Left");
        if (window.key_down(Key::Right)) print("Right");
        if (window.key_down(Key::Up)) print("Up");
        if (window.key_down(Key::Down)) print("Down");
        if (window.key_pressed(Key::Escape)) print("Escape");
        if (window.key_pressed(Key::Tab)) print("Tab");
        if (window.key_pressed(Key::Backspace)) print("Backspace");
        if (window.key_pressed(Key::Delete)) print("Delete");

        if (window.key_down('A')) print("A is down");
        if (window.key_pressed('B')) print("B pressed");
        if (window.key_released('C')) print("C released");

        window.clear(Black);
        window.draw_text(20, 20, "Press keys", White, 20);
        window.show();
    }
}

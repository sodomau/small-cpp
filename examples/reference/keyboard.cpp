void SmallMain()
{
    Window window;
    window.Open(640, 480);

    while (window.IsOpen())
    {
        if (window.KeyPressed(Key::Space)) Print("Space pressed");
        if (window.KeyReleased(Key::Enter)) Print("Enter released");
        if (window.KeyDown(Key::Left)) Print("Left");
        if (window.KeyDown(Key::Right)) Print("Right");
        if (window.KeyDown(Key::Up)) Print("Up");
        if (window.KeyDown(Key::Down)) Print("Down");
        if (window.KeyPressed(Key::Escape)) Print("Escape");
        if (window.KeyPressed(Key::Tab)) Print("Tab");
        if (window.KeyPressed(Key::Backspace)) Print("Backspace");
        if (window.KeyPressed(Key::Delete)) Print("Delete");

        if (window.KeyDown('A')) Print("A is down");
        if (window.KeyPressed('B')) Print("B pressed");
        if (window.KeyReleased('C')) Print("C released");

        window.Clear(Black);
        window.DrawText(20, 20, "Press keys", White, 20);
        window.Show();
    }
}

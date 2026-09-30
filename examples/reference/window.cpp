void SmallMain()
{
    Window window;

    Print("Default title: ", window.Title());

    window.SetTitle("Window Example");
    Print("Title before Open: ", window.Title());

    window.Open(400, 200);

    Print("Width: ", window.Width());
    Print("Height: ", window.Height());
    Print("Open: ", window.IsOpen());

    window.Clear(Black);
    window.DrawText(20, 20, "Title changes in one second.", White, 16);
    window.Show();

    Sleep(1.0);
    window.SetTitle("Level ", 2, " - Score: ", 100);

    Sleep(1.0);
    window.Close();

    Print("Open: ", window.IsOpen());
    Print("Title after Close: ", window.Title());
}

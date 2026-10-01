void SmallMain()
{
    File file;
    file.Open("friend.txt");
    Print(file.Input());
    file.Close();
    Input("Press Enter to close.");
}

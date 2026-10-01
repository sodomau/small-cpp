void SmallMain()
{
    File file;
    file.Open("message.txt");
    Print(file.Input());
    file.Close();
    Input("Press Enter to close.");
}

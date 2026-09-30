void SmallMain()
{
    File file;

    file.Open("profile.txt", FileMode::Write);
    file.Print("Alex");
    file.Print(12);
    file.Close();

    Print("Saved");
}

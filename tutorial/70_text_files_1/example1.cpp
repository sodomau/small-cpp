void SmallMain()
{
    File file;

    file.Open("score.txt", FileMode::Write);
    file.Print("Alex");
    file.Print(1200);
    file.Close();

    Print("Saved score.txt");
}

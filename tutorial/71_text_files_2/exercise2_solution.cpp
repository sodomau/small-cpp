void SmallMain()
{
    File file;

    file.Open("highscore.txt", FileMode::Write);
    file.Print(950);
    file.Close();

    file.Open("highscore.txt");
    int score = file.InputInt();
    file.Close();

    Print("High score: ", score);
}

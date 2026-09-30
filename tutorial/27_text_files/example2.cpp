void SmallMain()
{
    File file;

    file.Open("score.txt");

    String name = file.Input();
    int score = file.InputInt();

    file.Close();

    Print(name, "'s score: ", score);
}

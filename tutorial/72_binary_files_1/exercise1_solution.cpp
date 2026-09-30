void SmallMain()
{
    int level = 5;
    int score = 2300;
    double playTime = 18.75;

    File file;
    file.Open("game.dat", FileMode::WriteBinary);
    file.WriteInt(level);
    file.WriteInt(score);
    file.WriteReal(playTime);
    file.Close();

    Print("Saved");
}

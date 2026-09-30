void SmallMain()
{
    File file;

    file.Open("save.dat", FileMode::ReadBinary);

    int level = file.ReadInt();
    int score = file.ReadInt();
    double playTime = file.ReadReal();

    file.Close();

    Print("Level: ", level);
    Print("Score: ", score);
    Print("Play time: ", playTime);
}

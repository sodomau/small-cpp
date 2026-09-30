void SmallMain()
{
    int level = InputInt("Level: ");
    int score = InputInt("Score: ");
    double playTime = InputReal("Play time: ");

    // Save values using their native binary representations.
    File file;
    file.Open("save.dat", FileMode::WriteBinary);
    file.WriteInt(level);
    file.WriteInt(score);
    file.WriteReal(playTime);
    file.Close();

    Print("Game saved.");

    // Reopen the file and verify what was stored.
    file.Open("save.dat", FileMode::ReadBinary);
    int loadedLevel = file.ReadInt();
    int loadedScore = file.ReadInt();
    double loadedTime = file.ReadReal();
    file.Close();

    Print("Loaded level: ", loadedLevel);
    Print("Loaded score: ", loadedScore);
    Print("Loaded play time: ", loadedTime);
    Print("Native binary size: ",
          2 * sizeof(int) + sizeof(double), " bytes");
}

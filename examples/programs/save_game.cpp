void small_main()
{
    int level = input_int("Level: ");
    int score = input_int("Score: ");
    double play_time = input_real("Play time: ");

    // Save values using their native binary representations.
    File file;
    file.open("save.dat", FileMode::WriteBinary);
    file.write_int(level);
    file.write_int(score);
    file.write_real(play_time);
    file.close();

    print("Game saved.");

    // Reopen the file and verify what was stored.
    file.open("save.dat", FileMode::ReadBinary);
    int loaded_level = file.read_int();
    int loaded_score = file.read_int();
    double loaded_time = file.read_real();
    file.close();

    print("Loaded level: ", loaded_level);
    print("Loaded score: ", loaded_score);
    print("Loaded play time: ", loaded_time);
    print("Native binary size: ",
          2 * sizeof(int) + sizeof(double), " bytes");
}

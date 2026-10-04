void small_main()
{
    File file;

    file.open("save.dat", FileMode::ReadBinary);

    int level = file.read_int();
    int score = file.read_int();
    double play_time = file.read_real();

    file.close();

    print("Level: ", level);
    print("Score: ", score);
    print("Play time: ", play_time);
}

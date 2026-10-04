void small_main()
{
    int level = 5;
    int score = 2300;
    double play_time = 18.75;

    File file;
    file.open("game.dat", FileMode::WriteBinary);
    file.write_int(level);
    file.write_int(score);
    file.write_real(play_time);
    file.close();

    print("Saved");
}

void small_main()
{
    File file;

    file.open("highscore.txt", FileMode::Write);
    file.print(950);
    file.close();

    file.open("highscore.txt");
    int score = file.input_int();
    file.close();

    print("High score: ", score);
}

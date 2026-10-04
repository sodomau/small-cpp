void small_main()
{
    File file;

    file.open("score.txt");

    String name = file.input();
    int score = file.input_int();

    file.close();

    print(name, "'s score: ", score);
}

void small_main()
{
    File file;

    file.open("score.txt", FileMode::Write);
    file.print("Alex");
    file.print(1200);
    file.close();

    print("Saved score.txt");
}

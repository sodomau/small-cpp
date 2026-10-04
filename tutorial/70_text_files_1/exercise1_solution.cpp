void small_main()
{
    File file;

    file.open("profile.txt", FileMode::Write);
    file.print("Alex");
    file.print(12);
    file.close();

    print("Saved");
}

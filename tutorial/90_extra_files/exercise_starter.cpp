void small_main()
{
    File file;
    file.open("message.txt");
    print(file.input());
    file.close();
    input("Press Enter to close.");
}

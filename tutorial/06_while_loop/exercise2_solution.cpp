void SmallMain()
{
    int password = InputInt("Password: ");

    while (password != 1234)
    {
        Print("Try again.");
        password = InputInt("Password: ");
    }

    Print("Welcome!");
}

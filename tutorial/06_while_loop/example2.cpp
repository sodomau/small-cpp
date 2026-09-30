void SmallMain()
{
    int number = InputInt("Number (0 to stop): ");

    while (number != 0)
    {
        Print("You entered ", number);
        number = InputInt("Number (0 to stop): ");
    }

    Print("Done!");
}

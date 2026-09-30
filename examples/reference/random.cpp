void SmallMain()
{
    Print("Five dice rolls:");
    for (int i = 0; i < 5; i++)
        Print(RandomInt(1, 6));

    Print("Three random real numbers from 0.0 up to 1.0:");
    for (int i = 0; i < 3; i++)
        Print(RandomReal(0.0, 1.0));
}

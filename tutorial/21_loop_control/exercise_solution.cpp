void SmallMain()
{
    for (int i = 1; i <= 5; i = i + 1)
    {
        if (i == 3)
        {
            continue;
        }
        if (i == 5)
        {
            break;
        }
        Print(i);
    }
}

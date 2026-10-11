void small_main()
{
    for (int i = 1; i <= 5; i = i + 1)
    {
        if (i == 2)
        {
            continue;
        }
        if (i == 4)
        {
            break;
        }
        print(i);
    }
}

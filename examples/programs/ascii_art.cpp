void small_main()
{
    int size = input_int("Size: ");

    // Draw one row at a time.
    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            if (x == y || x == size - y - 1)
                write("X");
            else
                write(".");
        }
        print();
    }
}

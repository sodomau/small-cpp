int Max3(int a, int b, int c)
{
    int largest = a;

    if (b > largest)
        largest = b;

    if (c > largest)
        largest = c;

    return largest;
}

void SmallMain()
{
    Print(Max3(8, 3, 12));
}

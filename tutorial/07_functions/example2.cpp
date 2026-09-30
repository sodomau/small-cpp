int Square(int x)
{
    return x * x;
}

int Max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

void SmallMain()
{
    Print("Square: ", Square(6));
    Print("Larger: ", Max(7, 12));
}

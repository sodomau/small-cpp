void Swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

void SmallMain()
{
    int x = 3;
    int y = 7;

    Swap(x, y);

    Print(x, ", ", y);
}

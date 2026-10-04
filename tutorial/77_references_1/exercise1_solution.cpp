void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

void small_main()
{
    int x = 3;
    int y = 7;

    swap(x, y);

    print(x, ", ", y);
}

void AddOne(int x)
{
    x = x + 1;
    Print("Inside: ", x);
}

void SmallMain()
{
    int n = 10;

    AddOne(n);

    Print("Outside: ", n);
}

void add_one(int x)
{
    x = x + 1;
    print("Inside: ", x);
}

void small_main()
{
    int n = 10;

    add_one(n);

    print("Outside: ", n);
}

void small_main()
{
    Array<int> a(5);
    Array<int> b = {10, 20, 30};

    a[0] = 100;

    print("Length: ", a.length());
    print("First value: ", a[0]);

    a = b;
    print("New length: ", a.length());

    for (int i = 0; i < a.length(); i++)
        print(a[i]);

    Array<bool> flags = {true, false, true};
    flags[1] = true;
    print(flags[1]);
}

void SmallMain()
{
    Array<int> a(5);
    Array<int> b = {10, 20, 30};

    a[0] = 100;

    Print("Length: ", a.Length());
    Print("First value: ", a[0]);

    a = b;
    Print("New length: ", a.Length());

    for (int i = 0; i < a.Length(); i++)
        Print(a[i]);

    Array<bool> flags = {true, false, true};
    flags[1] = true;
    Print(flags[1]);
}

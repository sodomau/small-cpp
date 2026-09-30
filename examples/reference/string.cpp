void SmallMain()
{
    String a = "Hello";
    String b = "World";

    Print("Length: ", a.Length());
    Print("First character: ", a[0]);

    a[0] = 'Y';
    Print(a);

    Print(a.Substring(1));
    Print(a.Substring(1, 3));

    String c = a + " " + b;
    c += "!";
    Print(c);

    Print(a == b);
    Print(a != b);
    Print(a < b);
    Print(a <= b);
    Print(a > b);
    Print(a >= b);
}

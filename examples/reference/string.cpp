void small_main()
{
    String a = "Hello";
    String b = "World";

    print("Length: ", a.length());
    print("First character: ", a[0]);

    a[0] = 'Y';
    print(a);

    print(a.substring(1));
    print(a.substring(1, 3));

    String c = a + " " + b;
    c += "!";
    print(c);

    print(a == b);
    print(a != b);
    print(a < b);
    print(a <= b);
    print(a > b);
    print(a >= b);
}

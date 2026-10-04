void small_main()
{
    print("Hello, Small C++!");
    write("Two ", "words");
    print();

    String name = input("Name: ");
    int age = input_int("Age: ");
    double height = input_real("Height in meters: ");

    print("Hello, ", name, "!");
    print("Age: ", age);
    print("Height: ", height);

    String message = format("Name: ", name, ", age: ", age);
    print(message);
}

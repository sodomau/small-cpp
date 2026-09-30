void SmallMain()
{
    Print("Hello, Small C++!");
    Write("Two ", "words");
    Print();

    String name = Input("Name: ");
    int age = InputInt("Age: ");
    double height = InputReal("Height in meters: ");

    Print("Hello, ", name, "!");
    Print("Age: ", age);
    Print("Height: ", height);

    String message = Format("Name: ", name, ", age: ", age);
    Print(message);
}

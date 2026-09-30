void SmallMain()
{
    std::string text = "Hello";
    std::vector<int> numbers = {3, 7, 2, 9};

    Print(text);
    Print("Characters: ", text.size());
    Print("Numbers: ", numbers.size());
    Print("First number: ", numbers[0]);
}

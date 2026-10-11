void small_main()
{
    std::string text = "Hello";
    std::vector<int> numbers = {3, 7, 2, 9};

    print(text);
    print("Characters: ", text.size());
    print("Numbers: ", numbers.size());
    print("First number: ", numbers[0]);
}

int text_length(const std::string& text)
{
    return static_cast<int>(text.size());
}

void small_main()
{
    std::string text = "Small";
    print(text_length(text));
}

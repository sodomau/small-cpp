int TextLength(const std::string& text)
{
    return static_cast<int>(text.size());
}

void SmallMain()
{
    std::string text = "Small";
    Print(TextLength(text));
}

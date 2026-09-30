void SmallMain()
{
    String word = "Small";

    Print("First: ", word[0]);
    Print("Middle: ", word.Substring(1, 3));

    for (int i = 0; i < word.Length(); i = i + 1)
    {
        Print(i, ": ", word[i]);
    }
}

void SmallMain()
{
    String word = "Small";

    for (int i = word.Length() - 1; i >= 0; i = i - 1)
    {
        Print(word[i]);
    }
}

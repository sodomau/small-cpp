void SmallMain()
{
    String text = "Small C++";
    int index = -1;

    for (int i = 0; i < text.Length(); i = i + 1)
        if (text[i] == 'a')
        {
            index = i;
            break;
        }

    Print(index);
}

void small_main()
{
    String text = "Small C++";
    int index = -1;

    for (int i = 0; i < text.length(); i = i + 1)
        if (text[i] == 'a')
        {
            index = i;
            break;
        }

    print(index);
}

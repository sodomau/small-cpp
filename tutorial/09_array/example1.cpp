void SmallMain()
{
    Array<int> scores = {80, 95, 70, 100, 85};

    Print("Count: ", scores.Length());

    for (int i = 0; i < scores.Length(); i = i + 1)
    {
        Print(scores[i]);
    }
}

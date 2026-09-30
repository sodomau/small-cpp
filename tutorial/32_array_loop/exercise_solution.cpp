void SmallMain()
{
    Array<int> scores = {80, 95, 70};
    for (int i = 0; i < scores.Length(); i = i + 1)
    {
        Print(scores[i] * 2);
    }
}

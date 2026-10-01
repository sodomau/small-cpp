int AddPoints(int score, int points)
{
    return score + points;
}

void SmallMain()
{
    int score = 0;
    score = AddPoints(score, 10);
    score = AddPoints(score, 20);
    Print(score);
}

int add_points(int score, int points)
{
    return score + points;
}

void small_main()
{
    int score = 0;
    score = add_points(score, 10);
    score = add_points(score, 20);
    score = add_points(score, 5);
    print(score);
}

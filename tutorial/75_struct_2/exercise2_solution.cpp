struct Player
{
    String name;
    int score;
};

void small_main()
{
    Array<Player> players = {
        {"A", 10},
        {"B", 35},
        {"C", 20}
    };

    int best = 0;

    for (int i = 1; i < players.length(); i = i + 1)
        if (players[i].score > players[best].score)
            best = i;

    print(players[best].name);
}

struct Player
{
    String name;
    int score;
};

void SmallMain()
{
    Array<Player> players = {
        {"Alex", 800},
        {"Mina", 1200},
        {"Sam", 950}
    };

    int best = 0;

    for (int i = 1; i < players.Length(); i = i + 1)
        if (players[i].score > players[best].score)
            best = i;

    Print("Winner: ", players[best].name);
}

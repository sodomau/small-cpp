struct Player
{
    String name;
    int score;
};

void SmallMain()
{
    Player player;

    player.name = "Alex";
    player.score = 1200;

    Print(player.name, ": ", player.score);
}

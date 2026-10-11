struct Player
{
    String name;
    int score;
};

void small_main()
{
    Player player;

    player.name = "Alex";
    player.score = 1200;

    print(player.name, ": ", player.score);
}

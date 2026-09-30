void SmallMain()
{
    int secret = RandomInt(1, 100);
    int guess = 0;
    int tries = 0;

    Print("I am thinking of a number from 1 to 100.");

    // Keep asking until the player finds the secret.
    while (guess != secret)
    {
        guess = InputInt("Your guess: ");
        tries = tries + 1;

        if (guess < secret)
            Print("Too small!");
        else if (guess > secret)
            Print("Too large!");
    }

    Print("Correct! You needed ", tries, " guesses.");
    PlaySoundAndWait(Sound::Win);
}

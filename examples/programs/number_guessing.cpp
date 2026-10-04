void small_main()
{
    int secret = random_int(1, 100);
    int guess = 0;
    int tries = 0;

    print("I am thinking of a number from 1 to 100.");

    // Keep asking until the player finds the secret.
    while (guess != secret)
    {
        guess = input_int("Your guess: ");
        tries = tries + 1;

        if (guess < secret)
            print("Too small!");
        else if (guess > secret)
            print("Too large!");
    }

    print("Correct! You needed ", tries, " guesses.");
    play_sound_and_wait(Sound::Win);
}

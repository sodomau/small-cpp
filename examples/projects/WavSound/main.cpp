void small_main()
{
    // Optional: prepare the WAV before timing-sensitive gameplay.
    preload_sound("sound.wav");
    play_sound("sound.wav");
    print("The program keeps running while the sound plays.");
    sleep(1);
    play_sound_and_wait("sound.wav");
}

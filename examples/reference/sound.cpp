void small_main()
{
    play_sound_and_wait(Sound::Click);
    play_sound_and_wait(Sound::Pop);
    play_sound_and_wait(Sound::Jump);
    play_sound_and_wait(Sound::Hit);
    play_sound_and_wait(Sound::Coin);
    play_sound_and_wait(Sound::Shoot);
    play_sound_and_wait(Sound::Explosion);
    play_sound_and_wait(Sound::Win);
    play_sound_and_wait(Sound::Lose);

    play_sound(Sound::Pop);
    sleep(0.2);

    beep_and_wait(440, 0.3);
    beep(660, 0.3);
    sleep(0.4);
}

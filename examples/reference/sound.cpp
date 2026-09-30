void SmallMain()
{
    PlaySoundAndWait(Sound::Click);
    PlaySoundAndWait(Sound::Pop);
    PlaySoundAndWait(Sound::Jump);
    PlaySoundAndWait(Sound::Hit);
    PlaySoundAndWait(Sound::Coin);
    PlaySoundAndWait(Sound::Shoot);
    PlaySoundAndWait(Sound::Explosion);
    PlaySoundAndWait(Sound::Win);
    PlaySoundAndWait(Sound::Lose);

    PlaySound(Sound::Pop);
    Sleep(0.2);

    BeepAndWait(440, 0.3);
    Beep(660, 0.3);
    Sleep(0.4);
}

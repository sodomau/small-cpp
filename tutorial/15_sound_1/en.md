---
title: Play Sounds
part: making_things
part-title: Small Steps II — Making Things
goal: Play Sounds
related-example: reference/sound
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Playing sound effects

### What you will learn

**Playing sound** takes time. After a function call, the program may continue to its next task before the sound ends.

### Try it

@code example1.cpp

play_sound starts playback and returns immediately. Sound::Pop and Sound::Coin name built-in sound effects.

The example uses `sleep` to keep the program from ending immediately. Listen for the two effects starting in sequence.

## Waiting for a sound to finish

### What you will learn

Functions ending in **AndWait** wait for the sound to finish before returning.

### Try it

@code sound_2_example2.cpp

beep_and_wait's first value is the frequency in Hz, which sets pitch; the second is duration in seconds. Three rising tones at 440, 550, and 660 are followed by a sound effect.

When a game screen must keep moving, non-waiting play_sound or beep is convenient.

## Exercise

Play Click, Coin, and Win in order. Start each sound only after the previous one finishes.

@exercise exercise1_starter.cpp

### Hint

Use `play_sound_and_wait` three times.

@solution exercise1_solution.cpp

## Try More (Optional)

## Exercise

Use beep_and_wait to play three tones of different frequencies in sequence. Choose any frequencies and durations.

@exercise sound_2_exercise2_starter.cpp

### Hint

For example, play 440, 550, and 660 Hz for about 0.2 seconds each.

@solution sound_2_exercise2_solution.cpp

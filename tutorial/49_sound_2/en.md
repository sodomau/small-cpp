---
title: Waiting for a sound to finish
part: making_things
part-title: Small Steps II — Making Things
goal: Wait for a sound to finish.
related-example: reference/sound
---

## What you will learn

Functions ending in **AndWait** wait for the sound to finish before returning.

## Try it

@code example2.cpp

beep_and_wait's first value is the frequency in Hz, which sets pitch; the second is duration in seconds. Three rising tones at 440, 550, and 660 are followed by a sound effect.

When a game screen must keep moving, non-waiting play_sound or beep is convenient.

## Exercise

Use beep_and_wait to play three tones of different frequencies in sequence. Choose any frequencies and durations.

@exercise exercise2_starter.cpp

### Hint

For example, play 440, 550, and 660 Hz for about 0.2 seconds each.

@solution exercise2_solution.cpp

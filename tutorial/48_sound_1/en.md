---
title: Playing sound effects
part: making_things
part-title: Small Steps II — Making Things
goal: Play sound effects.
related-example: reference/sound
---

## What you will learn

**Playing sound** takes time. After a function call, the program may continue to its next task before the sound ends.

## Try it

@code example1.cpp

PlaySound starts playback and returns immediately. Sound::Pop and Sound::Coin name built-in sound effects.

The example uses Sleep to keep the program from ending immediately. Listen for the two effects starting in sequence.

## Exercise

Play Click, Coin, and Win in order. Start each sound only after the previous one finishes.

@exercise exercise1_starter.cpp

### Hint

Use `PlaySoundAndWait` three times.

@solution exercise1_solution.cpp

---
title: Changing once per key press
part: making_things
part-title: Small Steps II — Making Things
goal: Make one change for each new key press.
related-example: reference/keyboard
---

## What you will learn

**key_pressed** reports a new press. Distinguish it from key_down, which is true every frame while a key remains held.

## Try it

@code example2.cpp

When Space is newly pressed, `is_red = !is_red;` toggles true and false. That value chooses is_red or blue. Hold Space, release it, and press it again.

key_released reports the moment a key is released. Down is convenient for movement; Pressed is convenient for a single change.

## Exercise

Alternate the circle's radius between 20 and 60 each time Space is pressed. It must not keep changing while Space is held.

@exercise exercise2_starter.cpp

### Hint

Use `key_pressed(Key::Space)` and a bool variable to alternate between two states.

@solution exercise2_solution.cpp

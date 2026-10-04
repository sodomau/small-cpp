---
title: Moving while a key is held
part: making_things
part-title: Small Steps II — Making Things
goal: Move while a key is held.
related-example: reference/keyboard
---

## What you will learn

The **keyboard state** tells you which keys are currently held. key_down is true while a key is held down.

## Try it

@code example1.cpp

Change x and y with the arrow keys and redraw the circle at that position. The screen produced by one loop iteration is a **frame**.

`Key::Left` names the left arrow key. Hold the left and right arrow keys and check that the circle keeps moving.

## Exercise

Use W, A, S, and D instead of the arrow keys to move the circle up, left, down, and right.

@exercise exercise1_starter.cpp

### Hint

Check a letter key with `window.key_down('W')`.

@solution exercise1_solution.cpp

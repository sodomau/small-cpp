---
title: Use the Keyboard
part: making_things
part-title: Small Steps II — Making Things
goal: Use the Keyboard
related-example: reference/keyboard
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Moving while a key is held

### What you will learn

The **keyboard state** tells you which keys are currently held. key_down is true while a key is held down.

### Try it

@code example1.cpp

Change x and y with the arrow keys and redraw the circle at that position. The screen produced by one loop iteration is a **frame**.

`Key::Left` names the left arrow key. Hold the left and right arrow keys and check that the circle keeps moving.

## Changing once per key press

### What you will learn

**key_pressed** reports a new press. Distinguish it from key_down, which is true every frame while a key remains held.

### Try it

@code keyboard_2_example2.cpp

When Space is newly pressed, `is_red = !is_red;` toggles true and false. That value chooses is_red or blue. Hold Space, release it, and press it again.

key_released reports the moment a key is released. Down is convenient for movement; Pressed is convenient for a single change.

## Exercise

Use W, A, S, and D instead of the arrow keys to move the circle up, left, down, and right.

@exercise exercise1_starter.cpp

### Hint

Check a letter key with `window.key_down('W')`.

@solution exercise1_solution.cpp

## Try More (Optional)

## Exercise

Alternate the circle's radius between 20 and 60 each time Space is pressed. It must not keep changing while Space is held.

@exercise keyboard_2_exercise2_starter.cpp

### Hint

Use `key_pressed(Key::Space)` and a bool variable to alternate between two states.

@solution keyboard_2_exercise2_solution.cpp

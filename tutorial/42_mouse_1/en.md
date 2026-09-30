---
title: A circle that follows the mouse
part: making_things
part-title: Part II — Making Things
goal: Make a circle follow the mouse.
related-example: reference/mouse
---

## What you will learn

You can read the **mouse position** as x and y coordinates inside the window.

## Try it

@code example1.cpp

Use the position returned by MouseX and MouseY as the circle's center. Clearing the background and drawing at the new position each time makes one circle follow the mouse. Move the mouse inside the window.

## Exercise

Display a Yellow circle at the mouse position while the left button is held, and a small Gray circle when it is not held.

@exercise exercise1_starter.cpp

### Hint

Use `MouseDown(MouseButton::Left)` to separate the two cases.

@solution exercise1_solution.cpp

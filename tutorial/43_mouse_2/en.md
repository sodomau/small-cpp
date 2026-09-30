---
title: Responding to mouse buttons
part: making_things
part-title: Part II — Making Things
goal: Respond to mouse buttons.
related-example: reference/mouse
---

## What you will learn

The mouse's **position** and **button state** are separate. Reading both lets you act at the clicked location.

## Try it

@code example2.cpp

MouseDown(MouseButton::Left) asks whether the left button is held. The program draws a blue circle while held and a black outline when released.

MousePressed reports a new press; MouseReleased reports a release. Use Pressed to remember a position once.

## Exercise

Display a Red circle at the mouse position when the left button is held, and a Blue circle when the right button is held.

@exercise exercise2_starter.cpp

### Hint

Check MouseDown for Left and Right separately.

@solution exercise2_solution.cpp

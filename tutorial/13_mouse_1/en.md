---
title: Use the Mouse
part: making_things
part-title: Small Steps II — Making Things
goal: Use the Mouse
related-example: reference/mouse
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## A circle that follows the mouse

### What you will learn

You can read the **mouse position** as x and y coordinates inside the window.

### Try it

@code example1.cpp

Use the position returned by mouse_x and mouse_y as the circle's center. Clearing the background and drawing at the new position each time makes one circle follow the mouse. Move the mouse inside the window.

## Responding to mouse buttons

### What you will learn

The mouse's **position** and **button state** are separate. Reading both lets you act at the clicked location.

### Try it

@code mouse_2_example2.cpp

mouse_down(MouseButton::Left) asks whether the left button is held. The program draws a blue circle while held and a black outline when released.

mouse_pressed reports a new press; mouse_released reports a release. Use Pressed to remember a position once.

## Exercise

Display a Yellow circle at the mouse position while the left button is held, and a small Gray circle when it is not held.

@exercise exercise1_starter.cpp

### Hint

Use `mouse_down(MouseButton::Left)` to separate the two cases.

@solution exercise1_solution.cpp

## Try More (Optional)

## Exercise

Display a Red circle at the mouse position when the left button is held, and a Blue circle when the right button is held.

@exercise mouse_2_exercise2_starter.cpp

### Hint

Check mouse_down for Left and Right separately.

@solution mouse_2_exercise2_solution.cpp

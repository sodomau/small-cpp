---
title: Opening a window
part: making_things
part-title: Small Steps II — Making Things
goal: Open a window.
related-example: reference/window
---

## What you will learn

**Window** is a type for working with a window on the screen. An **object** is an actual instance of that type. Create an object named window and open a window.

## Try it

@code example1.cpp

`Open(640, 480)` opens a window 640 pixels wide and 480 pixels high. A **pixel** is a small dot making up the screen. `SetTitle` sets the title.

Repeat Show while IsOpen is true. Show displays the screen and handles input such as closing the window. This call is needed for the window to respond. The loop ends when you press its close button.

Later drawing examples reuse this window-opening structure.

## Exercise

Open a 500 × 300 Window and set its title to your name. Keep it open until it is closed.

@exercise exercise1_starter.cpp

### Hint

You can call `SetTitle` before `Open` too.

@solution exercise1_solution.cpp

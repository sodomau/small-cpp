---
title: Open and Use a Window
part: making_things
part-title: Small Steps II — Making Things
goal: Open and Use a Window
related-example: reference/window
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Opening a window

### What you will learn

**Window** is a type for working with a window on the screen. An **object** is an actual instance of that type. Create an object named window and open a window.

### Try it

@code example1.cpp

`open(640, 480)` opens a window 640 pixels wide and 480 pixels high. A **pixel** is a small dot making up the screen. `set_title` sets the title.

Repeat `show` while is_open is true. `show` displays the screen and handles input such as closing the window. This call is needed for the window to respond. The loop ends when you press its close button.

Later drawing examples reuse this window-opening structure.

## Asking an object for information

### What you will learn

Writing a function name after an object's dot uses an operation belonging to that object. Such a function is a **member function**.

### Try it

@code first_window_2_example2.cpp

`window.width()` and `window.height()` return the window's width and height. Check that the console shows `Size: 400 x 300`.

Creating the object and opening the actual window are separate actions. You can call set_title before `open`. Call `close` to close it from your program.

## Exercise

Open a 500 × 300 Window and set its title to your name. Keep it open until it is closed.

@exercise exercise1_starter.cpp

### Hint

You can call `set_title` before `open` too.

@solution exercise1_solution.cpp

## Try More (Optional)

## Exercise

Open a 320 × 240 window, print its actual `width` and `height` in the console, and keep the window open.

@exercise first_window_2_exercise2_starter.cpp

### Hint

Pass `window.width()` and `window.height()` to `print`.

@solution first_window_2_exercise2_solution.cpp

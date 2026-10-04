---
title: Asking an object for information
part: making_things
part-title: Small Steps II — Making Things
goal: Ask an object for information.
related-example: reference/window
---

## What you will learn

Writing a function name after an object's dot uses an operation belonging to that object. Such a function is a **member function**.

## Try it

@code example2.cpp

`window.width()` and `window.height()` return the window's width and height. Check that the console shows `Size: 400 x 300`.

Creating the object and opening the actual window are separate actions. You can call set_title before `open`. Call `close` to close it from your program.

## Exercise

Open a 320 × 240 window, print its actual `width` and `height` in the console, and keep the window open.

@exercise exercise2_starter.cpp

### Hint

Pass `window.width()` and `window.height()` to `print`.

@solution exercise2_solution.cpp

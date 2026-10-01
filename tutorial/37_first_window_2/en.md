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

`window.Width()` and `window.Height()` return the window's width and height. Check that the console shows `Size: 400 x 300`.

Creating the object and opening the actual window are separate actions. You can call SetTitle before Open. Call Close to close it from your program.

## Exercise

Open a 320 × 240 window, print its actual Width and Height in the console, and keep the window open.

@exercise exercise2_starter.cpp

### Hint

Pass `window.Width()` and `window.Height()` to Print.

@solution exercise2_solution.cpp

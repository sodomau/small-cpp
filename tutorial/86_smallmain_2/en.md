---
title: Cleaning up the window before the runtime
part: cpp
part-title: Small Steps VI — Growing into C++
goal: Clean up the window before shutting down the runtime.
related-example: reference/console
---

## What you will learn

A **runtime** provides the foundation for features such as windows and sound. Clean up objects using those features before shutting down their foundation.

## Try it

@code example2.cpp

When the inner brace scope ends, the Window object is cleaned up. Then call ShutdownSmall. Closing a window and ending an object's lifetime are different actions.

argc and argv receive information passed on the command line. This lesson is optional advanced material. You do not need to memorize all pointer notation yet.

## Exercise

Write `#include <small.h>` and `int main(int argc, char* argv[])`. Pass argc and argv to `Small::InitializeSmall`, print argc, and call `Small::ShutdownSmall()` before the program finishes.

@exercise exercise2_starter.cpp

### Hint

After `Small::InitializeSmall(argc, argv);`, use `Small::Print("argc: ", argc);`. Call `Small::ShutdownSmall();` before `return 0;`.

@solution exercise2_solution.cpp

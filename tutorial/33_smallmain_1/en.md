---
title: Understand the Program Entry Point
part: cpp
part-title: Small Steps VI — Growing into C++
goal: Understand the Program Entry Point
related-example: reference/console
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Writing the real entry function main

### What you will learn

**main** is the entry function of a C++ program. Until now, Small supplied main and had it call small_main. Now write setup and shutdown yourself.

### Try it

@code example1.cpp

Writing your own main in this IDE also ends automatic header and namespace support. That is why you include small.h and use Small::.

Follow initialize_small → your work → shutdown_small. return 0 indicates normal termination. Check for Hello from main!.

## Cleaning up the window before the runtime

### What you will learn

A **runtime** provides the foundation for features such as windows and sound. Clean up objects using those features before shutting down their foundation.

### Try it

@code smallmain_2_example2.cpp

When the inner brace scope ends, the Window object is cleaned up. Then call shutdown_small. Closing a window and ending an object's lifetime are different actions.

argc and argv receive information passed on the command line. This lesson is optional advanced material. You do not need to memorize all pointer notation yet.

## Exercise

Change a small_main Hello program to a real `main()`. Write `#include <small.h>` yourself and use `Small::initialize_small()`, `Small::print`, and `Small::shutdown_small()`.

@exercise exercise1_starter.cpp

### Hint

Do more than rename the function: use return type `int`, call `Small::shutdown_small();` before finishing, and then write `return 0;`.

@solution exercise1_solution.cpp

## Try More (Optional)

## Exercise

Write `#include <small.h>` and `int main(int argc, char* argv[])`. Pass argc and argv to `Small::initialize_small`, print argc, and call `Small::shutdown_small()` before the program finishes.

@exercise smallmain_2_exercise2_starter.cpp

### Hint

After `Small::initialize_small(argc, argv);`, use `Small::print("argc: ", argc);`. Call `Small::shutdown_small();` before `return 0;`.

@solution smallmain_2_exercise2_solution.cpp

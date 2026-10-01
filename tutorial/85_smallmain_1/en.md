---
title: Writing the real entry function main
part: cpp
part-title: Small Steps VI — Growing into C++
goal: Write the real entry function main.
related-example: reference/console
---

## What you will learn

**main** is the entry function of a C++ program. Until now, Small supplied main and had it call SmallMain. Now write setup and shutdown yourself.

## Try it

@code example1.cpp

Writing your own main in this IDE also ends automatic header and namespace support. That is why you include small.h and use Small::.

Follow InitializeSmall → your work → ShutdownSmall. return 0 indicates normal termination. Check for Hello from main!.

## Exercise

Change a SmallMain Hello program to a real `main()`. Write `#include <small.h>` yourself and use `Small::InitializeSmall()`, `Small::Print`, and `Small::ShutdownSmall()`.

@exercise exercise1_starter.cpp

### Hint

Do more than rename the function: use return type `int`, call `Small::ShutdownSmall();` before finishing, and then write `return 0;`.

@solution exercise1_solution.cpp

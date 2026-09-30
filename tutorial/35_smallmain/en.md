---
title: The Secret of SmallMain()
part: cpp
part-title: Part VI — Growing into C++
goal: See that SmallMain is an ordinary function called by Small, then write main yourself.
related-example: reference/console
---

## The Secret of SmallMain()

`SmallMain` is not special C++ syntax. Small's hidden entry point effectively performs:

`main() → Small::InitializeSmall(...) → SmallMain() → Small::ShutdownSmall()`

When you write `main()` yourself, you also take responsibility for the Small runtime lifetime. Call `Small::InitializeSmall()` before using runtime features and `Small::ShutdownSmall()` before leaving `main()`.

## Examples

@code example1.cpp

Read the code from top to bottom, predict what it will do, then use **Try This Code** and run your copy. Change one small detail and observe the result.

@code example2.cpp

## Exercise 1

Convert the starter into a complete `main()` program. Initialize Small, run the program body, call `Small::ShutdownSmall()`, and then return 0.

@exercise exercise1_starter.cpp

### Hint

Use this lifecycle: `InitializeSmall()` → your program → `ShutdownSmall()` → `return 0;`.

@solution exercise1_solution.cpp

## Exercise 2

Pass `argc` and `argv` to `Small::InitializeSmall`, print `argc`, then call `Small::ShutdownSmall()` before returning.

@exercise exercise2_starter.cpp

### Hint

Do not omit shutdown: call `Small::ShutdownSmall();` immediately before `return 0;`.

@solution exercise2_solution.cpp

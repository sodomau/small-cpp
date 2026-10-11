---
title: Write C++ without Small
part: cpp
part-title: Small Steps VI — Growing into C++
goal: Write C++ without Small
related-example: reference/console
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Greeting without Small

### What you will learn

Using only the standard tools you have learned lets you do the same work without Small.

### Try it

@code example1.cpp

Use main instead of small_main, std::string instead of String, getline instead of `input`, and cout instead of `print`. Entering Alex produces Hello, Alex.

Because no Small features are used, small.h, initialize_small, and shutdown_small are unnecessary too.

## Using the same procedures in standard C++

### What you will learn

Even when tool notation changes, **storing values, looping, and accumulating a sum** remain the same procedures.

### Try it

@code beyond_2_example2.cpp

Add the vector's values with a range-based for and print the value returned by a function with cout. The result is Sum: 25.

Variables, conditions, loops, and functions learned so far all work in ordinary C++ too. Keep learning new tools as you need them for things you want to make.

## Exercise

Write a main program that adds all values in a `std::vector<int>` and prints the sum with `std::cout`, using no Small API.

@exercise exercise1_starter.cpp

### Hint

Write `#include <iostream>` and `#include <vector>` yourself.

@solution exercise1_solution.cpp

## Try More (Optional)

## Exercise

Create `greet` taking a `const std::string&`, printing `Hello, name!` with std::cout, and call it from main.

@exercise beyond_2_exercise2_starter.cpp

### Hint

You need `#include <iostream>` and `#include <string>`.

@solution beyond_2_exercise2_solution.cpp

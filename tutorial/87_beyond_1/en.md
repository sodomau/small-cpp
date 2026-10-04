---
title: Greeting without Small
part: cpp
part-title: Small Steps VI — Growing into C++
goal: Write a greeting without Small.
related-example: reference/console
---

## What you will learn

Using only the standard tools you have learned lets you do the same work without Small.

## Try it

@code example1.cpp

Use main instead of small_main, std::string instead of String, getline instead of `input`, and cout instead of `print`. Entering Alex produces Hello, Alex.

Because no Small features are used, small.h, initialize_small, and shutdown_small are unnecessary too.

## Exercise

Write a main program that adds all values in a `std::vector<int>` and prints the sum with `std::cout`, using no Small API.

@exercise exercise1_starter.cpp

### Hint

Write `#include <iostream>` and `#include <vector>` yourself.

@solution exercise1_solution.cpp

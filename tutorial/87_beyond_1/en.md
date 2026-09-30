---
title: Greeting without Small
part: cpp
part-title: Part VI — Growing into C++
goal: Write a greeting without Small.
related-example: reference/console
---

## What you will learn

Using only the standard tools you have learned lets you do the same work without Small.

## Try it

@code example1.cpp

Use main instead of SmallMain, std::string instead of String, getline instead of Input, and cout instead of Print. Entering Alex produces Hello, Alex.

Because no Small features are used, small.h, InitializeSmall, and ShutdownSmall are unnecessary too.

## Exercise

Write a main program that adds all values in a `std::vector<int>` and prints the sum with `std::cout`, using no Small API.

@exercise exercise1_starter.cpp

### Hint

Write `#include <iostream>` and `#include <vector>` yourself.

@solution exercise1_solution.cpp

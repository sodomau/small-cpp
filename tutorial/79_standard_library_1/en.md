---
title: Using tools that already exist
part: cpp
part-title: Part VI — Growing into C++
goal: Use tools that already exist.
related-example: reference/console
---

## What you will learn

A **library** is a collection of tools made for use in programs. The C++ standard library provides common tools across different environments.

## Try it

@code example1.cpp

std::min returns the smaller of two values; std::max returns the larger. The expected output is Min: 3 and Max: 12.

std:: marks a name belonging to the standard library. For now, Small IDE prepares the basic headers you need.

## Exercise

Use `std::min` and `std::max` on the ints 17 and 42 and print the smaller and larger values.

@exercise exercise1_starter.cpp

### Hint

You can put a standard function directly inside Print, as in `Print(std::min(17, 42));`.

@solution exercise1_solution.cpp

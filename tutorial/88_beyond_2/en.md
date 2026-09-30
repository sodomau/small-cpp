---
title: Using the same procedures in standard C++
part: cpp
part-title: Part VI — Growing into C++
goal: Use the same procedures in standard C++.
related-example: reference/console
---

## What you will learn

Even when tool notation changes, **storing values, looping, and accumulating a sum** remain the same procedures.

## Try it

@code example2.cpp

Add the vector's values with a range-based for and print the value returned by a function with cout. The result is Sum: 25.

Variables, conditions, loops, and functions learned so far all work in ordinary C++ too. Keep learning new tools as you need them for things you want to make.

## Exercise

Create `Greet` taking a `const std::string&`, printing `Hello, name!` with std::cout, and call it from main.

@exercise exercise2_starter.cpp

### Hint

You need `#include <iostream>` and `#include <string>`.

@solution exercise2_solution.cpp

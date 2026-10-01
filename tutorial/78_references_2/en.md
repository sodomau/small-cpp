---
title: Reading without copying
part: types
part-title: Small Steps V — Making Your Own Types
goal: Read without copying.
related-example: reference/array
---

## What you will learn

A **const reference** lets you read the original without copying it, while promising not to change it through that reference.

## Try it

@code example2.cpp

In `const Array<int>& numbers`, & marks a reference to the original and const makes it read-only. The output is Sum: 25.

The sum needs no copy of the whole array. Attempting to change it causes a compilation error. The earlier Array<int> parameter is also valid, but copying can be costly for large arrays.

## Exercise

Change the earlier `FindLargest(Array<int> numbers)` to use `const Array<int>&`. The function does not modify the Array.

@exercise exercise2_starter.cpp

### Hint

Change only the parameter to `const Array<int>& numbers`; the algorithm can stay the same.

@solution exercise2_solution.cpp

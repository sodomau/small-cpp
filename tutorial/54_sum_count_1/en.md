---
title: Adding values in order
part: algorithms
part-title: Small Steps III — Thinking with Programs
goal: Add values in order.
related-example: reference/array
---

## What you will learn

An **algorithm** is a procedure for finding an answer. Calculate a sum by remembering the total so far and adding the next value.

## Try it

@code example1.cpp

total changes from 0 → 3 → 10 → 12 → 21 → 25. The expected output is Sum: 25.

Before any values have been added, their sum is 0, so the initial value is 0. Creating total with 0 inside every iteration prevents accumulation.

## Exercise

Find an Array's sum, divide by its number of values, and print the average. Make total a double so the division can produce a fractional result.

@exercise exercise1_starter.cpp

### Hint

Start with `double total = 0;` and calculate `total / numbers.length()` at the end.

@solution exercise1_solution.cpp

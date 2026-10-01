---
title: Counting occurrences of the largest value
part: algorithms
part-title: Small Steps III — Thinking with Programs
goal: Count occurrences of the largest value.
related-example: reference/array
---

## What you will learn

Combining two procedures you already know can solve a new problem.

## Try it

@code example2.cpp

First find the maximum, then use a second loop to count elements equal to it. The output is Largest: 9 and How many: 2.

Make each step's responsibility clear before trying to combine the two loops. The array must contain at least one element.

## Exercise

First find the Array's largest value, then count how often it occurs in a second loop.

@exercise exercise2_starter.cpp

### Hint

The first loop finds largest; the second counts occurrences of `numbers[i] == largest`.

@solution exercise2_solution.cpp

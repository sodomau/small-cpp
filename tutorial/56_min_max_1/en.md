---
title: Remembering the largest value so far
part: algorithms
part-title: Small Steps III — Thinking with Programs
goal: Remember the largest value seen so far.
related-example: reference/array
---

## What you will learn

**Finding a maximum** means remembering the largest value seen so far and replacing it when a larger one appears.

## Try it

@code example1.cpp

Start with the first element, 7. 2 is smaller, so nothing changes; 9 is larger, so it replaces the remembered value. The result is Largest: 9.

Starting at 0 may be wrong when all values are negative. This example uses an array with at least one element.

## Exercise

Find and print the smallest value in the Array.

@exercise exercise1_starter.cpp

### Hint

Use the first value as smallest and compare from index 1 onward.

@solution exercise1_solution.cpp

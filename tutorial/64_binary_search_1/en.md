---
title: Halving the search range
part: algorithms
part-title: Small Steps III — Thinking with Programs
goal: Halve the search range.
related-example: reference/array
---

## What you will learn

**Binary search** compares with the middle value and repeatedly halves the possible range. The array must first be sorted from smallest to largest.

## Try it

@code example1.cpp

left and right mark the remaining range's ends. If the target is smaller than the middle value, discard the right half; if larger, discard the left half.

11 is at position 5. Return -1 if not found. Because middle was already checked, exclude it from the next range.

## Exercise

Write Binary Search to find 23 in the sorted array `{4, 8, 15, 16, 23, 42}` and print its index.

@exercise exercise1_starter.cpp

### Hint

Use left, right, and middle, reducing the range by half each time.

@solution exercise1_solution.cpp

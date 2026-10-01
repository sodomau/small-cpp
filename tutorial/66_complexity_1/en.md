---
title: How much work does more data require?
part: algorithms
part-title: Small Steps III — Thinking with Programs
goal: Understand how the amount of work grows with more data.
related-example: reference/array
---

## What you will learn

**Time complexity** describes how the amount of required work grows as the number of data items increases. It is different from actual seconds.

## Try it

@code example1.cpp

When a linear search fails, it checks all n elements. With n equal to 10, 100, and 1000, the worst-case comparison counts are also 10, 100, and 1000.

This growth is written O(n). Rather than measuring time, the example displays the amount of work numerically.

## Exercise

Imagine a Linear Search for an absent value among 20 values. Count and print the actual comparisons.

@exercise exercise1_starter.cpp

### Hint

Increase comparisons for each value inspected and make the search reach the end without a match.

@solution exercise1_solution.cpp

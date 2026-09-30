---
title: Ordering from smallest to largest
part: algorithms
part-title: Part III — Thinking with Programs
goal: Order values from smallest to largest.
related-example: reference/array
---

## What you will learn

**Sorting** changes an order according to a rule. This method finds the smallest remaining value and fills positions from the front.

## Try it

@code example1.cpp

The outer loop selects the position i to fill; the inner loop finds the minimum's index in the remaining part.

Use temp to hold one value temporarily when swapping. Overwriting it immediately would lose the original. Check that the output is 2, 4, 5, 7, 9.

## Exercise

Use Selection Sort to arrange `{10, 3, 8, 1, 6}` from smallest to largest.

@exercise exercise1_starter.cpp

### Hint

Apply the lesson's smallest-index pattern.

@solution exercise1_solution.cpp

---
title: Finding the second-largest value
part: algorithms
part-title: Part III — Thinking with Programs
goal: Find the second-largest value.
related-example: reference/array
---

## What you will learn

Before solving a new problem, define **what counts as the answer and what assumptions hold about the input**. Here we remember two candidates.

## Try it

@code example1.cpp

The example assumes at least two elements and includes duplicates in the ranking. For {9, 9, 3}, the answer is 9. It does not mean the second distinct value.

When a new maximum appears, move the previous maximum into second. For 8, 3, 12, 5, 10, the answer is 10.

## Exercise

Assume there are at least two distinct values and find the second-smallest value.

@exercise exercise1_starter.cpp

### Hint

Remember smallest and second. When a value is smaller than smallest, update both values together.

@solution exercise1_solution.cpp

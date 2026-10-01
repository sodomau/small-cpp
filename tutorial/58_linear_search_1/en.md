---
title: Searching for a value
part: algorithms
part-title: Small Steps III — Thinking with Programs
goal: Search for a value.
related-example: reference/array
---

## What you will learn

**Searching** determines whether a value exists and, if so, where it is. Comparing values one by one from the beginning is called linear search.

## Try it

@code example1.cpp

9 is at position 2, so the output is Index: 2. When found, return gives back the position and ends the whole function.

If the value is not found by the end, return -1. Valid positions are at least 0, so -1 was chosen to mean not found.

## Exercise

When a value appears several times, find its last index. Print -1 if it does not occur.

@exercise exercise1_starter.cpp

### Hint

Instead of returning at the first match, update the index and keep looking to the end.

@solution exercise1_solution.cpp

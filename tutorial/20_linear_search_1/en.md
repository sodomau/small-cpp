---
title: Find a Value
part: algorithms
part-title: Small Steps III — Thinking with Programs
goal: Find a Value
related-example: reference/array
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Searching for a value

### What you will learn

**Searching** determines whether a value exists and, if so, where it is. Comparing values one by one from the beginning is called linear search.

### Try it

@code example1.cpp

9 is at position 2, so the output is Index: 2. When found, return gives back the position and ends the whole function.

If the value is not found by the end, return -1. Valid positions are at least 0, so -1 was chosen to mean not found.

## Handling the not-found case

### What you will learn

A search can succeed or fail. The program should distinguish and report both cases.

### Try it

@code linear_search_2_example2.cpp

Entering 9 in the console produces Found at 2; entering 8 produces Not found.

Here, break ends only the search loop, and the following if prints the result. Distinguish this from return, which ends the whole function.

## Exercise

When a value appears several times, find its last index. Print -1 if it does not occur.

@exercise exercise1_starter.cpp

### Hint

Instead of returning at the first match, update the index and keep looking to the end.

@solution exercise1_solution.cpp

## Try More (Optional)

## Exercise

Use a linear search to find and print the first position of the character 'a' in a String. Use -1 if absent.

@exercise linear_search_2_exercise2_starter.cpp

### Hint

String also supports `length` and [], so this is almost the same as searching an Array.

@solution linear_search_2_exercise2_solution.cpp

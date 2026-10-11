---
title: Search by Halving
part: algorithms
part-title: Small Steps III — Thinking with Programs
goal: Search by Halving
related-example: reference/array
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Halving the search range

### What you will learn

**Binary search** compares with the middle value and repeatedly halves the possible range. The array must first be sorted from smallest to largest.

### Try it

@code example1.cpp

left and right mark the remaining range's ends. If the target is smaller than the middle value, discard the right half; if larger, discard the left half.

11 is at position 5. Return -1 if not found. Because middle was already checked, exclude it from the next range.

## Seeing which values were compared

### What you will learn

Printing intermediate values lets you trace how a program finds its answer.

### Try it

@code binary_search_2_example2.cpp

The example searches for 23 and prints Checking 12 and Checking 23. There are 2 comparisons.

This example is for observing comparisons. Changing value to an absent value ends the loop when the range becomes empty, but it does not print a separate success message.

## Exercise

Write Binary Search to find 23 in the sorted array `{4, 8, 15, 16, 23, 42}` and print its index.

@exercise exercise1_starter.cpp

### Hint

Use left, right, and middle, reducing the range by half each time.

@solution exercise1_solution.cpp

## Try More (Optional)

## Exercise

Add a counter to Binary Search and print how many comparisons it made to find the value.

@exercise binary_search_2_exercise2_starter.cpp

### Hint

Increase comparisons by 1 each time the while loop runs.

@solution binary_search_2_exercise2_solution.cpp

---
title: Find the Largest Value
part: algorithms
part-title: Small Steps III — Thinking with Programs
goal: Find the Largest Value
related-example: reference/array
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Remembering the largest value so far

### What you will learn

**Finding a maximum** means remembering the largest value seen so far and replacing it when a larger one appears.

### Try it

@code example1.cpp

Start with the first element, 7. 2 is smaller, so nothing changes; 9 is larger, so it replaces the remembered value. The result is Largest: 9.

Starting at 0 may be wrong when all values are negative. This example uses an array with at least one element.

## Remembering a value's position

### What you will learn

Remembering an **index** instead of a value lets you know both what the smallest value is and where it is.

### Try it

@code min_max_2_example2.cpp

smallest_index is the position of the smallest element. Read its value with `numbers[smallest_index]`. In this example, the smallest value is 1 at position 3.

Index in the variable name helps distinguish a position from a value. If the minimum occurs several times, the current < comparison keeps its first occurrence.

## Exercise

Find and print the smallest value in the Array.

@exercise exercise1_starter.cpp

### Hint

Use the first value as smallest and compare from index 1 onward.

@solution exercise1_solution.cpp

## Try More (Optional)

## Exercise

Find the index of the largest value, and print both the value and its index.

@exercise min_max_2_exercise2_starter.cpp

### Hint

Start largest_index at 0 and compare `numbers[i] > numbers[largest_index]`.

@solution min_max_2_exercise2_solution.cpp

---
title: Remembering a value's position
part: algorithms
part-title: Small Steps III — Thinking with Programs
goal: Remember the position of a value.
related-example: reference/array
---

## What you will learn

Remembering an **index** instead of a value lets you know both what the smallest value is and where it is.

## Try it

@code example2.cpp

smallest_index is the position of the smallest element. Read its value with `numbers[smallest_index]`. In this example, the smallest value is 1 at position 3.

Index in the variable name helps distinguish a position from a value. If the minimum occurs several times, the current < comparison keeps its first occurrence.

## Exercise

Find the index of the largest value, and print both the value and its index.

@exercise exercise2_starter.cpp

### Hint

Start largest_index at 0 and compare `numbers[i] > numbers[largest_index]`.

@solution exercise2_solution.cpp

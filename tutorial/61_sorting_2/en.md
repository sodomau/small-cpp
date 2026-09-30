---
title: Ordering from largest to smallest
part: algorithms
part-title: Part III — Thinking with Programs
goal: Order values from largest to smallest.
related-example: reference/array
---

## What you will learn

Changing the comparison rule changes the order without changing the procedure. Listing larger values first is **descending order**.

## Try it

@code example2.cpp

Now find the largest remaining value. The comparison changes from < to >, and the output becomes 9, 7, 5, 4, 2.

You do not need to rebuild the whole loop to change sorting direction. Change which value is selected first.

## Exercise

Modify Selection Sort to arrange values from largest to smallest.

@exercise exercise2_starter.cpp

### Hint

Find largest instead of smallest, and change the comparison to `>`.

@solution exercise2_solution.cpp

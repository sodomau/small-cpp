---
title: Seeing which values were compared
part: algorithms
part-title: Part III — Thinking with Programs
goal: See which values were compared.
related-example: reference/array
---

## What you will learn

Printing intermediate values lets you trace how a program finds its answer.

## Try it

@code example2.cpp

The example searches for 23 and prints Checking 12 and Checking 23. There are 2 comparisons.

This example is for observing comparisons. Changing value to an absent value ends the loop when the range becomes empty, but it does not print a separate success message.

## Exercise

Add a counter to Binary Search and print how many comparisons it made to find the value.

@exercise exercise2_starter.cpp

### Hint

Increase comparisons by 1 each time the while loop runs.

@solution exercise2_solution.cpp

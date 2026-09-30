---
title: How many times can a range be halved?
part: algorithms
part-title: Part III — Thinking with Programs
goal: Understand how often a range can be halved.
related-example: reference/array
---

## What you will learn

Halving a range each time makes the iteration count grow slowly even as the data grows. This growth is called O(log n).

## Try it

@code example2.cpp

Repeatedly halve 1024 using integer division. Processing 1024, 512, …, 1 produces Steps: 11.

This is the example's iteration count, not the exact comparison count of every binary search. Big-O summarizes a growth trend.

## Exercise

Start at n=1000 and keep dividing by 2 until n becomes 0. Count the steps required.

@exercise exercise2_starter.cpp

### Hint

In while, divide with `n = n / 2` and increase count.

@solution exercise2_solution.cpp

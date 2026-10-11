---
title: How Much Work Does a Program Do? (Optional)
part: algorithms
part-title: Small Steps III — Thinking with Programs
goal: How Much Work Does a Program Do? (Optional)
related-example: reference/array
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## How much work does more data require?

### What you will learn

**Time complexity** describes how the amount of required work grows as the number of data items increases. It is different from actual seconds.

### Try it

@code example1.cpp

When a linear search fails, it checks all n elements. With n equal to 10, 100, and 1000, the worst-case comparison counts are also 10, 100, and 1000.

This growth is written O(n). Rather than measuring time, the example displays the amount of work numerically.

## How many times can a range be halved?

### What you will learn

Halving a range each time makes the iteration count grow slowly even as the data grows. This growth is called O(log n).

### Try it

@code complexity_2_example2.cpp

Repeatedly halve 1024 using integer division. Processing 1024, 512, …, 1 produces Steps: 11.

This is the example's iteration count, not the exact comparison count of every binary search. Big-O summarizes a growth trend.

## Exercise

Imagine a Linear Search for an absent value among 20 values. Count and print the actual comparisons.

@exercise exercise1_starter.cpp

### Hint

Increase comparisons for each value inspected and make the search reach the end without a match.

@solution exercise1_solution.cpp

## Try More (Optional)

## Exercise

Start at n=1000 and keep dividing by 2 until n becomes 0. Count the steps required.

@exercise complexity_2_exercise2_starter.cpp

### Hint

In while, divide with `n = n / 2` and increase count.

@solution complexity_2_exercise2_solution.cpp

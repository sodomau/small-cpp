---
title: Calculate Totals and Counts
part: algorithms
part-title: Small Steps III — Thinking with Programs
goal: Calculate Totals and Counts
related-example: reference/array
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Adding values in order

### What you will learn

An **algorithm** is a procedure for finding an answer. Calculate a sum by remembering the total so far and adding the next value.

### Try it

@code example1.cpp

total changes from 0 → 3 → 10 → 12 → 21 → 25. The expected output is Sum: 25.

Before any values have been added, their sum is 0, so the initial value is 0. Creating total with 0 inside every iteration prevents accumulation.

## Counting matching values

### What you will learn

To count matches, add 1 only when you encounter an element that meets the condition.

### Try it

@code sum_count_2_example2.cpp

`numbers[i] % 2 == 0` asks whether division by 2 has remainder 0: whether the number is even. 8, 4, and 10 match, producing Even: 3. Zero also meets this condition.

count_even takes an array parameter. Here, it receives a copy of an Array<int> value; later lessons on references show how to avoid copying.

## Exercise

Find an Array's sum, divide by its number of values, and print the average. Make total a double so the division can produce a fractional result.

@exercise exercise1_starter.cpp

### Hint

Start with `double total = 0;` and calculate `total / numbers.length()` at the end.

@solution exercise1_solution.cpp

## Try More (Optional)

## Exercise

Count and print how many values in the Array are greater than 0.

@exercise sum_count_2_exercise2_starter.cpp

### Hint

Check `numbers[i] > 0` for each value and increase count by 1 when true.

@solution sum_count_2_exercise2_solution.cpp

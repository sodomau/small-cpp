---
title: Counting matching values
part: algorithms
part-title: Small Steps III — Thinking with Programs
goal: Count values that meet a condition.
related-example: reference/array
---

## What you will learn

To count matches, add 1 only when you encounter an element that meets the condition.

## Try it

@code example2.cpp

`numbers[i] % 2 == 0` asks whether division by 2 has remainder 0: whether the number is even. 8, 4, and 10 match, producing Even: 3. Zero also meets this condition.

CountEven takes an array parameter. Here, it receives a copy of an Array<int> value; later lessons on references show how to avoid copying.

## Exercise

Count and print how many values in the Array are greater than 0.

@exercise exercise2_starter.cpp

### Hint

Check `numbers[i] > 0` for each value and increase count by 1 when true.

@solution exercise2_solution.cpp

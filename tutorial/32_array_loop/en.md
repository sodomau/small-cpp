---
title: Looking at array values one at a time
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Print twice each score. You do not need to store the results back in the array.
related-example: reference/console
---

## What you will learn

Using a loop variable as an array index lets you read the elements in order. length() tells you how many elements there are.

## Try it

@code example.cpp

The program prints when i is 0, 1, and 2. At 3, i equals the number of elements and the condition becomes false. That is why the condition uses `<`, not `<=`. A length of 0 runs no iterations.

Expected output:

```text
80
95
70
```

## Exercise

Print twice each score. You do not need to store the results back in the array.

@exercise exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution exercise_solution.cpp

---
title: Repeating while a condition holds
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Print backwards from 5 to 1.
related-example: reference/console
---

## What you will learn

**while** repeats the code inside braces while its condition is true. It checks the condition before every iteration.

## Try it

@code example.cpp

The loop ends when count becomes 0. If it starts at 0, nothing is printed. Removing the line that decreases count makes the loop run forever; use the IDE's Stop button in that case.

for is convenient when counting iterations; while is convenient when waiting for a condition to change.

Expected output:

```text
3
2
1
```

## Exercise

Print backwards from 5 to 1.

@exercise exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution exercise_solution.cpp

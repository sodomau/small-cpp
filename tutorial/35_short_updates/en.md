---
title: Shorter ways to update a value
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Start the score at 10, double it, then increase it by 1 and print it.
related-example: reference/console
---

## What you will learn

You can shorten commonly used calculations and assignments. For int or double, `score += 5;` makes the same update as `score = score + 5;`.

## Try it

@code example.cpp

`++` increases by 1; `--` decreases by 1. At first, use them as separate statements as in the example. `-=`, `*=`, and `/=` work similarly. Integers also support `%=`. Integer /= still performs integer division.

Expected output:

```text
14
```

## Exercise

Start the score at 10, double it, then increase it by 1 and print it.

@exercise exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution exercise_solution.cpp

---
title: Calculating with a remembered value
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Create lives with the value 3, reduce it by 1, and print it.
related-example: reference/console
---

## What you will learn

You can use stored values in calculations. Store the result again to increase a score.

## Try it

@code example.cpp

`score = score + 5;` first reads the current value 10, adds 5, then stores the result 15 in score. It does not mean that both sides are equal, as a mathematical equation would.

Running only `print(score + 5);` displays the calculated result but does not change score itself.

Expected output:

```text
15
```

## Exercise

Create lives with the value 3, reduce it by 1, and print it.

@exercise exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution exercise_solution.cpp

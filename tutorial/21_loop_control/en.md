---
title: Stopping or skipping an iteration
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Skip 3 instead of 2, and stop at 5.
related-example: reference/console
---

## What you will learn

**break** ends the innermost loop. **continue** skips the rest of the current iteration and moves to the next one.

## Try it

@code example.cpp

At 2, Print is skipped. for increases i and checks the next condition. At 4, the entire loop ends, so neither 4 nor 5 is printed.

Expected output:

```text
1
3
```

## Exercise

Skip 3 instead of 2, and stop at 5.

@exercise exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution exercise_solution.cpp

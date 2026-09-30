---
title: Combining two conditions
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Print Outside when the age is below 13 or above 19. Test with 20.
related-example: reference/console
---

## What you will learn

`&&` means **both conditions are true**, `||` means **at least one is true**, and `!` reverses true and false.

## Try it

@code example.cpp

Check whether the age is at least 13 and at most 19. Try 12, 13, 19, and 20 to check the boundaries.

`!ready` asks whether you are not ready. && skips the right side if the left is false; || skips it if the left is true.

Expected output:

```text
Teen
```

## Exercise

Print Outside when the age is below 13 or above 19. Test with 20.

@exercise exercise_starter.cpp

### Hint

Use || between the two conditions.

@solution exercise_solution.cpp

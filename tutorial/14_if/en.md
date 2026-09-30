---
title: Running only when a condition holds
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Print Positive only when number is greater than 0. Test with 3 first.
related-example: reference/console
---

## What you will learn

A **condition** is an expression that can be true or false. if is a **conditional statement** that runs the code inside its braces only when the condition is true.

## Try it

@code example.cpp

`score >= 60` asks whether the score is at least 60. With 80, it is true and prints Pass. Change it to 50: Pass is skipped and only Done is printed.

`>` means greater than, `<` less than, `>=` at least, and `<=` at most. Do not put a ; after the closing brace of if.

Expected output:

```text
Pass
Done
```

## Exercise

Print Positive only when number is greater than 0. Test with 3 first.

@exercise exercise_starter.cpp

### Hint

Also change 3 to 0 and -1. Those cases should produce no output.

@solution exercise_solution.cpp

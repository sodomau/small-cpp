---
title: Quotients and remainders
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Print the number of bags and the number left over when you put 18 candies into bags of 5.
related-example: reference/console
---

## What you will learn

`/` divides; `%` gives the remainder of integer division. With 17 candies and 5 per bag, you can fill three bags and have 2 candies left over.

## Try it

@code example.cpp

Dividing integers discards the fractional part. `5 / 2` is 2, but when either operand is double, as in `5.0 / 2`, the result is 2.5. Merely changing the receiving variable to double does not change the already calculated result of `5 / 2`.

Do not divide by zero. Like multiplication, / and % are calculated before addition.

Expected output:

```text
3
2
2.5
```

## Exercise

Print the number of bags and the number left over when you put 18 candies into bags of 5.

@exercise exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution exercise_solution.cpp

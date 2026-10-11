---
title: Calculate with Numbers
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Calculate with Numbers
related-example: reference/console
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Calculating and displaying numbers

### What you will learn

Write numbers without double quotes. `+` adds and `-` subtracts. These are **operators**: symbols for operations.

### Try it

@code example.cpp

`3 + 5` is an **expression** that calculates the value 8. `"3 + 5"` is a string containing those exact characters, so it is not calculated.

Expected output:

```text
8
7
3 + 5
```

## Multiplication and calculation order

### What you will learn

`*` means multiplication. Multiplication happens before addition. You can also use parentheses to group the part to calculate first.

### Try it

@code multiply_example.cpp

The first line calculates 3 × 4 first. The second calculates 2 + 3 inside parentheses first. Use parentheses to make the order of a complicated expression clear.

Expected output:

```text
14
20
```

## Quotients and remainders

### What you will learn

`/` divides; `%` gives the remainder of integer division. With 17 candies and 5 per bag, you can fill three bags and have 2 candies left over.

### Try it

@code division_example.cpp

Dividing integers discards the fractional part. `5 / 2` is 2, but when either operand is double, as in `5.0 / 2`, the result is 2.5. Merely changing the receiving variable to double does not change the already calculated result of `5 / 2`.

Do not divide by zero. Like multiplication, / and % are calculated before addition.

Expected output:

```text
3
2
2.5
```

## Exercise

Print 12 plus 7, then 12 minus 7.

@exercise exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution exercise_solution.cpp

## Try More (Optional)

## Exercise

Store a width of 3.5 and a height of 2.0 in double variables, calculate the area, and print it.

@exercise multiply_exercise_starter.cpp

### Hint

Even when the product is 7.0, it may appear as 7 on the screen.

@solution multiply_exercise_solution.cpp

## Exercise

Print the number of bags and the number left over when you put 18 candies into bags of 5.

@exercise division_exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution division_exercise_solution.cpp

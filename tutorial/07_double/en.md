---
title: Storing values with fractional parts
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Store a running time of 12.5 in a variable named seconds and print it.
related-example: reference/console
---

## What you will learn

Lengths and times may need fractional parts. **double** is a type for these numbers. Choose int for whole-number counts and double for values that need a fractional part.

## Try it

@code example.cpp

A variable's type is chosen when it is created. Assigning a fractional number to an int later does not turn it into a double variable.

double cannot store every number with unlimited precision, but for now we will start with simple lengths and times.

Expected output:

```text
1.45
```

## Exercise

Store a running time of 12.5 in a variable named seconds and print it.

@exercise exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution exercise_solution.cpp

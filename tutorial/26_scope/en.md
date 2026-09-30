---
title: Using separate variables inside a function
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Predict the two outputs when score starts at 20, then check your prediction.
related-example: reference/console
---

## What you will learn

A **local variable** created inside a function is used within its scope. A parameter passed by value also holds a value separately from the original.

## Try it

@code example.cpp

number receives a copy of score's value, 10. Only number changes, so score is still 10 when the function returns.

Ordinary local variables reach the end of their lifetime when their scope ends. They do not automatically remember a value for the next call. Later lessons on references show how to change the original.

Expected output:

```text
11
10
```

## Exercise

Predict the two outputs when score starts at 20, then check your prediction.

@exercise exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution exercise_solution.cpp

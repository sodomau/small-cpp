---
title: Giving a value a name
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Store 10 in an int variable named age and print it.
related-example: reference/console
---

## What you will learn

A **variable** is a named place to store a value. Let us remember a score under the name score.

## Try it

@code example.cpp

`int score = 10;` creates a variable named score and gives it the initial value 10. **int is an integer type**. A type describes the kind of value stored; integers such as 0, 10, and -3 have no fractional part.

Creating a variable is called **declaration**; giving it its first value is **initialization**. For now, always give a variable a value when you create it. `print(score);` prints the stored value, rather than the letters score.

Expected output:

```text
10
```

## Exercise

Store 10 in an int variable named age and print it.

@exercise exercise_starter.cpp

### Hint

Use the name age instead of score.

@solution exercise_solution.cpp

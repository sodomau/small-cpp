---
title: Creating an array by choosing its size
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Create five positions, store 1 through 5 in them, and print them.
related-example: reference/console
---

## What you will learn

Instead of listing initial values, you can choose the number of positions first. Array<int>(3) creates three positions for integers.

## Try it

@code example.cpp

`Array<int> numbers(3);` has three positions. `Array<int> numbers = {3};` has one position containing the value 3. Keep the two forms distinct.

Small Array has no operation to increase its length after creation. You can still change each element's value.

Expected output:

```text
1
2
3
```

## Exercise

Create five positions, store 1 through 5 in them, and print them.

@exercise exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution exercise_solution.cpp

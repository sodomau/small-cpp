---
title: Use Arrays
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Use Arrays
related-example: reference/console
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Keeping several values together

### What you will learn

An **array** is an ordered collection of values of the same type. Small's Array<int> is a type that holds several integers.

### Try it

@code example.cpp

One value in an array is an **element**; its position number is an **index**. Like string positions, indices start at 0. With three elements, valid indices are 0, 1, and 2. Brackets let you read or change a value.

Expected output:

```text
80
100
```

## Looking at array values one at a time

### What you will learn

Using a loop variable as an array index lets you read the elements in order. length() tells you how many elements there are.

### Try it

@code array_loop_example.cpp

The program prints when i is 0, 1, and 2. At 3, i equals the number of elements and the condition becomes false. That is why the condition uses `<`, not `<=`. A length of 0 runs no iterations.

Expected output:

```text
80
95
70
```

## Creating an array by choosing its size

### What you will learn

Instead of listing initial values, you can choose the number of positions first. Array<int>(3) creates three positions for integers.

### Try it

@code array_create_example.cpp

`Array<int> numbers(3);` has three positions. `Array<int> numbers = {3};` has one position containing the value 3. Keep the two forms distinct.

Small Array has no operation to increase its length after creation. You can still change each element's value.

Expected output:

```text
1
2
3
```

## Exercise

Change the third score to 90 and print it.

@exercise exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution exercise_solution.cpp

## Try More (Optional)

## Exercise

Print twice each score. You do not need to store the results back in the array.

@exercise array_loop_exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution array_loop_exercise_solution.cpp

## Exercise

Create five positions, store 1 through 5 in them, and print them.

@exercise array_create_exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution array_create_exercise_solution.cpp

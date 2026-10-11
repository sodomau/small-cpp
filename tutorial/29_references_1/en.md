---
title: Use References
part: types
part-title: Small Steps V — Making Your Own Types
goal: Use References
related-example: reference/array
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Naming the original instead of copying

### What you will learn

A **reference** is another name for an existing object. An int& parameter refers to the original integer passed in.

### Try it

@code example1.cpp

First run the example: it prints Inside: 11 and Outside: 10. Change `add_one(int x)` to `add_one(int& x)` and run again. Now both are 11.

Initially x was a copy; after adding &, it is another name for n. Use this when you intend to change the original.

## Reading without copying

### What you will learn

A **const reference** lets you read the original without copying it, while promising not to change it through that reference.

### Try it

@code references_2_example2.cpp

In `const Array<int>& numbers`, & marks a reference to the original and const makes it read-only. The output is Sum: 25.

The sum needs no copy of the whole array. Attempting to change it causes a compilation error. The earlier Array<int> parameter is also valid, but copying can be costly for large arrays.

## Exercise

Create `swap(int& a, int& b)` to exchange the original values of two ints.

@exercise exercise1_starter.cpp

### Hint

Save a temporarily in temp, then assign a=b and b=temp.

@solution exercise1_solution.cpp

## Try More (Optional)

## Exercise

Change the earlier `find_largest(Array<int> numbers)` to use `const Array<int>&`. The function does not modify the Array.

@exercise references_2_exercise2_starter.cpp

### Hint

Change only the parameter to `const Array<int>& numbers`; the algorithm can stay the same.

@solution references_2_exercise2_solution.cpp

---
title: Naming the original instead of copying
part: types
part-title: Small Steps V — Making Your Own Types
goal: Name the original instead of copying it.
related-example: reference/array
---

## What you will learn

A **reference** is another name for an existing object. An int& parameter refers to the original integer passed in.

## Try it

@code example1.cpp

First run the example: it prints Inside: 11 and Outside: 10. Change `AddOne(int x)` to `AddOne(int& x)` and run again. Now both are 11.

Initially x was a copy; after adding &, it is another name for n. Use this when you intend to change the original.

## Exercise

Create `Swap(int& a, int& b)` to exchange the original values of two ints.

@exercise exercise1_starter.cpp

### Hint

Save a temporarily in temp, then assign a=b and b=temp.

@solution exercise1_solution.cpp

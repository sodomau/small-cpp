---
title: Grouping data and operations
part: types
part-title: Part V — Making Your Own Types
goal: Group data and operations.
related-example: programs/bouncing_ball
---

## What you will learn

A **class** groups data with operations on that data. An **object** is an actual instance of its type. This lesson introduces the idea that you can make such tools yourself.

## Try it

@code example1.cpp

A Counter object holds its counted value. Calling AddOne twice and reading Value gives 2.

public exposes a part to users; private prevents direct access from outside. You have already used String and Window as objects with data and related operations. Constructors and inheritance are beyond this lesson.

## Exercise

Add a public `Reset()` to Counter that sets its value to 0, and check that it works.

@exercise exercise1_starter.cpp

### Hint

Assign 0 to the private value inside Reset.

@solution exercise1_solution.cpp

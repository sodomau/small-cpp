---
title: Combine Data and Behavior with Classes
part: types
part-title: Small Steps V — Making Your Own Types
goal: Combine Data and Behavior with Classes
related-example: programs/bouncing_ball
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Grouping data and operations

### What you will learn

A **class** groups data with operations on that data. An **object** is an actual instance of its type. This lesson introduces the idea that you can make such tools yourself.

### Try it

@code example1.cpp

A Counter object holds its counted value. Calling `add_one` twice and reading `get_value()` gives 2.

public exposes a part to users; private prevents direct access from outside. You have already used String and Window as objects with data and related operations. Constructors and inheritance are beyond this lesson.

## Exercise

Add a public `reset()` to Counter that sets its value to 0, and check that it works.

@exercise exercise1_starter.cpp

### Hint

Assign 0 to the private value inside `reset`.

@solution exercise1_solution.cpp

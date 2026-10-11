---
title: Use the Standard Library
part: cpp
part-title: Small Steps VI — Growing into C++
goal: Use the Standard Library
related-example: reference/console
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Using tools that already exist

### What you will learn

A **library** is a collection of tools made for use in programs. The C++ standard library provides common tools across different environments.

### Try it

@code example1.cpp

std::min returns the smaller of two values; std::max returns the larger. The expected output is Min: 3 and Max: 12.

std:: marks a name belonging to the standard library. For now, Small IDE prepares the basic headers you need.

## Finding the magnitude of a negative number

### What you will learn

An **absolute value** is a number's distance from 0 on the number line. Find it with std::abs.

### Try it

@code standard_library_2_example2.cpp

The absolute value of -12 is 12. The expected output is Absolute: 12 and Smaller: -12.

Knowing a function's name, input, and result lets you use it without recreating its implementation. Value ranges are limited, so practice with small integers here.

## Exercise

Use `std::min` and `std::max` on the ints 17 and 42 and print the smaller and larger values.

@exercise exercise1_starter.cpp

### Hint

You can put a standard function directly inside `print`, as in `print(std::min(17, 42));`.

@solution exercise1_solution.cpp

## Try More (Optional)

## Exercise

Find and print the absolute value of -25 using `std::abs`.

@exercise standard_library_2_exercise2_starter.cpp

### Hint

`std::abs(-25)` returns the int 25.

@solution standard_library_2_exercise2_solution.cpp

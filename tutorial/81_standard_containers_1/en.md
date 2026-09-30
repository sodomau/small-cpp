---
title: Meeting standard strings and arrays
part: cpp
part-title: Part VI — Growing into C++
goal: Meet standard strings and arrays.
related-example: reference/console
---

## What you will learn

A **container** holds several values. std::string and std::vector are standard tools corresponding to the strings and arrays you know.

## Try it

@code example1.cpp

The length operation is named size() instead of Length(). The example prints Hello, Characters: 5, Numbers: 4, and First number: 3.

Bracket positions still start at 0. Do not expect standard containers' [] to report out-of-range errors the way Small does.

## Exercise

Create a `std::vector<int>` containing 5 and 10, add another value with `push_back(15)`, and print them all.

@exercise exercise1_starter.cpp

### Hint

Use a range-based for such as `for (int value : numbers)` to visit every value.

@solution exercise1_solution.cpp

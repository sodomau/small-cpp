---
title: Adding elements and reading them one by one
part: cpp
part-title: Small Steps VI — Growing into C++
goal: Add elements and read them one by one.
related-example: reference/console
---

## What you will learn

std::vector lets you append elements. A **range-based for** visits a container's elements one at a time.

## Try it

@code example2.cpp

push_back(40) appends 40. `for (int value : numbers)` receives each element's value in value and adds it to a total. The result is Sum: 100.

Here value is a copied integer, so changing it does not change an array element. size() may have a type different from int; check types when handling large sizes.

## Exercise

Create `text_length` taking a `const std::string&` and returning its length. Print the length of "Small".

@exercise exercise2_starter.cpp

### Hint

`text.size()` returns a standard C++ unsigned size type. This exercise returns int, so explicitly convert with `static_cast<int>(text.size())` before returning.

@solution exercise2_solution.cpp

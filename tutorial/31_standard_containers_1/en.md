---
title: Use Standard Strings and Containers
part: cpp
part-title: Small Steps VI — Growing into C++
goal: Use Standard Strings and Containers
related-example: reference/console
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Meeting standard strings and arrays

### What you will learn

A **container** holds several values. std::string and std::vector are standard tools corresponding to the strings and arrays you know.

### Try it

@code example1.cpp

The length operation is named size() instead of length(). The example prints Hello, Characters: 5, Numbers: 4, and First number: 3.

Bracket positions still start at 0. Do not expect standard containers' [] to report out-of-range errors the way Small does.

## Adding elements and reading them one by one

### What you will learn

std::vector lets you append elements. A **range-based for** visits a container's elements one at a time.

### Try it

@code standard_containers_2_example2.cpp

push_back(40) appends 40. `for (int value : numbers)` receives each element's value in value and adds it to a total. The result is Sum: 100.

Here value is a copied integer, so changing it does not change an array element. size() may have a type different from int; check types when handling large sizes.

## Exercise

Create a `std::vector<int>` containing 5 and 10, add another value with `push_back(15)`, and print them all.

@exercise exercise1_starter.cpp

### Hint

Use a range-based for such as `for (int value : numbers)` to visit every value.

@solution exercise1_solution.cpp

## Try More (Optional)

## Exercise

Create `text_length` taking a `const std::string&` and returning its length. Print the length of "Small".

@exercise standard_containers_2_exercise2_starter.cpp

### Hint

`text.size()` returns a standard C++ unsigned size type. This exercise returns int, so explicitly convert with `static_cast<int>(text.size())` before returning.

@solution standard_containers_2_exercise2_solution.cpp

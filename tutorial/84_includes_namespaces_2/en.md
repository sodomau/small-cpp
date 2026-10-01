---
title: Showing where a name belongs
part: cpp
part-title: Small Steps VI — Growing into C++
goal: Show where a name belongs.
related-example: reference/console
---

## What you will learn

A **namespace** groups names to distinguish them. :: identifies the namespace a name belongs to.

## Try it

@code example2.cpp

Small::Print and std::cout are different tools. The example prints Small namespace and Standard namespace in that order.

A namespace is not an object. Distinguish the dot in window.Show() from :: in Small::Print.

## Exercise

Create `std::string name`, read a line with `std::getline(std::cin, name)`, and print it back with `std::cout`.

@exercise exercise2_starter.cpp

### Hint

Include `<iostream>` and `<string>`, print a prompt with cout, then call getline.

@solution exercise2_solution.cpp

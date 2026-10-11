---
title: Understand Headers and Namespaces
part: cpp
part-title: Small Steps VI — Growing into C++
goal: Understand Headers and Namespaces
related-example: reference/console
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Writing down the tools you need

### What you will learn

A **header** provides declarations so you can use tools from other code. #include is a directive to include that header.

### Try it

@code example1.cpp

Include iostream for standard input/output and string for std::string. std::cout << value produces output; std::getline(std::cin, name) reads a line. Entering Alex produces Hello, Alex.

Keep small_main this time and change only the input/output tools.

## Showing where a name belongs

### What you will learn

A **namespace** groups names to distinguish them. :: identifies the namespace a name belongs to.

### Try it

@code includes_namespaces_2_example2.cpp

Small::print and std::cout are different tools. The example prints Small namespace and Standard namespace in that order.

A namespace is not an object. Distinguish the dot in window.show() from :: in Small::print.

## Exercise

Write `#include <iostream>` and use `std::cout` to print `Hello C++` and a newline. Keep using `small_main()` for now.

@exercise exercise1_starter.cpp

### Hint

Send values to the output stream as in `std::cout << "Hello C++" << "\n";`.

@solution exercise1_solution.cpp

## Try More (Optional)

## Exercise

Create `std::string name`, read a line with `std::getline(std::cin, name)`, and print it back with `std::cout`.

@exercise includes_namespaces_2_exercise2_starter.cpp

### Hint

Include `<iostream>` and `<string>`, print a prompt with cout, then call getline.

@solution includes_namespaces_2_exercise2_solution.cpp

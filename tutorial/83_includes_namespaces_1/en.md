---
title: Writing down the tools you need
part: cpp
part-title: Small Steps VI — Growing into C++
goal: Write down the tools you need.
related-example: reference/console
---

## What you will learn

A **header** provides declarations so you can use tools from other code. #include is a directive to include that header.

## Try it

@code example1.cpp

Include iostream for standard input/output and string for std::string. std::cout << value produces output; std::getline(std::cin, name) reads a line. Entering Alex produces Hello, Alex.

Keep SmallMain this time and change only the input/output tools.

## Exercise

Write `#include <iostream>` and use `std::cout` to print `Hello C++` and a newline. Keep using `SmallMain()` for now.

@exercise exercise1_starter.cpp

### Hint

Send values to the output stream as in `std::cout << "Hello C++" << "\n";`.

@solution exercise1_solution.cpp

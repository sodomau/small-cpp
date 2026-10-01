---
title: Grouping related values
part: types
part-title: Small Steps V — Making Your Own Types
goal: Group related values.
related-example: reference/array
---

## What you will learn

**struct** defines a new type grouping related values. Put a name and score together in one Player.

## Try it

@code example1.cpp

String and int are existing types; Player is a type we create. Access the values inside it with a dot, as in player.name.

The example prints Alex: 1200. A struct definition needs a ; after its closing brace.

## Exercise

Create a `Point` struct with double x and y. Store (3.5, 7.0) and print the values.

@exercise exercise1_starter.cpp

### Hint

Start with `struct Point { double x; double y; };`.

@solution exercise1_solution.cpp

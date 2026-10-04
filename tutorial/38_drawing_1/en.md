---
title: Drawing with coordinates
part: making_things
part-title: Small Steps II — Making Things
goal: Draw with coordinates.
related-example: reference/drawing
---

## What you will learn

**Coordinates** are numbers describing a screen position. The top-left corner is (0, 0); x increases to the right and y increases downwards.

## Try it

@code example1.cpp

Clear clears the background. `fill_circle(320, 240, 80, Yellow)` fills a yellow circle centered at (320, 240) with radius 80. draw_circle draws only its outline.

draw_line's four numbers are the starting x and y and the ending x and y. Later drawings cover earlier ones. When you see the yellow face, try changing a circle's position.

Braces can be omitted for a single statement, as with while at the end of the example. You may use braces when writing it yourself.

## Exercise

Draw a traffic light with three vertically arranged Red, Yellow, and Green circles inside a black or Gray rectangle.

@exercise exercise1_starter.cpp

### Hint

First draw the body with fill_rectangle, then use fill_circle three times.

@solution exercise1_solution.cpp

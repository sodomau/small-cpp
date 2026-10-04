---
title: Adding colors and text
part: making_things
part-title: Small Steps II — Making Things
goal: Add colors and text.
related-example: reference/drawing
---

## What you will learn

**rgb** makes a color by mixing the intensities of red, green, and blue. Each value ranges from 0 to 255.

## Try it

@code example2.cpp

Color is the type that stores a color; rgb is a function that creates and returns one.

fill_rectangle takes the top-left x and y and the width and height. draw_rectangle draws only the outline. draw_text takes x, y, a string, a color, and a font size. Check that the text appears over the orange rectangle.

## Exercise

Draw a simple face with circles and lines. Include two eyes and a mouth. Choose any colors and positions.

@exercise exercise2_starter.cpp

### Hint

Make a face with one large fill_circle, then add two small circles and a draw_line.

@solution exercise2_solution.cpp

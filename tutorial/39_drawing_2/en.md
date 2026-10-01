---
title: Adding colors and text
part: making_things
part-title: Small Steps II — Making Things
goal: Add colors and text.
related-example: reference/drawing
---

## What you will learn

**RGB** makes a color by mixing the intensities of red, green, and blue. Each value ranges from 0 to 255.

## Try it

@code example2.cpp

Color is the type that stores a color; RGB is a function that creates and returns one.

FillRectangle takes the top-left x and y and the width and height. DrawRectangle draws only the outline. DrawText takes x, y, a string, a color, and a font size. Check that the text appears over the orange rectangle.

## Exercise

Draw a simple face with circles and lines. Include two eyes and a mouth. Choose any colors and positions.

@exercise exercise2_starter.cpp

### Hint

Make a face with one large FillCircle, then add two small circles and a DrawLine.

@solution exercise2_solution.cpp

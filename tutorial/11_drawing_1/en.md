---
title: Draw Shapes and Text
part: making_things
part-title: Small Steps II — Making Things
goal: Draw Shapes and Text
related-example: reference/drawing
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Drawing with coordinates

### What you will learn

**Coordinates** are numbers describing a screen position. The top-left corner is (0, 0); x increases to the right and y increases downwards.

### Try it

@code example1.cpp

Clear clears the background. `fill_circle(320, 240, 80, Yellow)` fills a yellow circle centered at (320, 240) with radius 80. draw_circle draws only its outline.

draw_line's four numbers are the starting x and y and the ending x and y. Later drawings cover earlier ones. When you see the yellow face, try changing a circle's position.

Braces can be omitted for a single statement, as with while at the end of the example. You may use braces when writing it yourself.

## Adding colors and text

### What you will learn

**rgb** makes a color by mixing the intensities of red, green, and blue. Each value ranges from 0 to 255.

### Try it

@code drawing_2_example2.cpp

Color is the type that stores a color; rgb is a function that creates and returns one.

fill_rectangle takes the top-left x and y and the width and height. draw_rectangle draws only the outline. draw_text takes x, y, a string, a color, and a font size. Check that the text appears over the orange rectangle.

## Exercise

Draw a traffic light with three vertically arranged Red, Yellow, and Green circles inside a black or Gray rectangle.

@exercise exercise1_starter.cpp

### Hint

First draw the body with fill_rectangle, then use fill_circle three times.

@solution exercise1_solution.cpp

## Try More (Optional)

## Exercise

Draw a simple face with circles and lines. Include two eyes and a mouth. Choose any colors and positions.

@exercise drawing_2_exercise2_starter.cpp

### Hint

Make a face with one large fill_circle, then add two small circles and a draw_line.

@solution drawing_2_exercise2_solution.cpp

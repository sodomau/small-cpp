---
title: Pixels
goal: Read and change individual Image pixels using Pixel and SetPixel.
---

## An image is a grid of pixels

Change a pixel's color with `SetPixel(x, y, color)` and read it with `Pixel(x, y)`. As in Window, (0, 0) is the top-left corner.

## Try it first

@code example1.cpp

## Creating pixels makes algorithms visible

Two nested loops visiting every pixel let you build gradients, patterns, and simple image processing yourself. Out-of-range pixel coordinates are reported as errors.

## One step further

@code example2.cpp

## Pixel work and drawing are separate

Changing data inside Image is a member operation. Displaying the result in a Window uses `DrawImage`.

## Exercise — A diagonal

Draw a Yellow diagonal from (0, 0) to (99, 99) in a 100 × 100 Black image.

@exercise exercise1_starter.cpp

### Hint

Use the loop's i for both x and y.

@solution exercise1_solution.cpp

## Exercise — Read a pixel

Read pixel (10, 10) in a Red image and print its red component.

@exercise exercise2_starter.cpp

### Hint

After `Color color = image.Pixel(10, 10);`, use `color.Red()`.

@solution exercise2_solution.cpp

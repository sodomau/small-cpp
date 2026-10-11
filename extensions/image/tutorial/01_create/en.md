---
title: Create and Manipulate Images
goal: Create and Manipulate Images
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Creating Images

### The first Image extension

Image belongs to an extension, rather than Core. Write `#include <small/image.h>` at the top. Small IDE sees this include and automatically links the Image extension.

### Try it first

@code example1.cpp

### Image and Window are different things

`Image` owns image data and provides operations intrinsic to an image, such as `width()`, `height()`, and `pixel()`. `draw_image(window, image, ...)` is a free function because it connects Image and Window.

Omitting a size draws at the original size. Supplying width and height smoothly scales it to that size.

### One step further

@code example2.cpp

### Extensions are ordinary C++ too

Using Image does not mean learning a new language. You include a header and use ordinary C++ objects and functions.

## Pixels

### An image is a grid of pixels

Change a pixel's color with `set_pixel(x, y, color)` and read it with `pixel(x, y)`. As in Window, (0, 0) is the top-left corner.

### Try it first

@code pixels_example1.cpp

### Creating pixels makes algorithms visible

Two nested loops visiting every pixel let you build gradients, patterns, and simple image processing yourself. Out-of-range pixel coordinates are reported as errors.

### One step further

@code pixels_example2.cpp

### Pixel work and drawing are separate

Changing data inside Image is a member operation. Displaying the result in a Window uses `draw_image`.

## Exercise — Draw at two sizes

Create a 120 × 80 Green image. Draw it at its original size and twice that size in one window.

@exercise exercise1_starter.cpp

### Hint

Use both the four-argument and six-argument forms of `draw_image`.

@solution exercise1_solution.cpp

## Exercise — Check the size

Create a 64 × 48 image and print its Width and Height.

@exercise exercise2_starter.cpp

### Hint

Use `print(image.width(), " x ", image.height());`.

@solution exercise2_solution.cpp

## Try More (Optional)

## Exercise — A diagonal

Draw a Yellow diagonal from (0, 0) to (99, 99) in a 100 × 100 Black image.

@exercise pixels_exercise1_starter.cpp

### Hint

Use the loop's i for both x and y.

@solution pixels_exercise1_solution.cpp

## Exercise — Read a pixel

Read pixel (10, 10) in a Red image and print its red component.

@exercise pixels_exercise2_starter.cpp

### Hint

After `Color color = image.pixel(10, 10);`, use `color.red()`.

@solution pixels_exercise2_solution.cpp

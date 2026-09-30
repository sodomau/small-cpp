---
title: Creating Images
goal: Create Image objects in memory and draw them in a Window.
---

## The first Image extension

Image belongs to an extension, rather than Core. Write `#include <small/image.h>` at the top. Small IDE sees this include and automatically links the Image extension.

## Try it first

@code example1.cpp

## Image and Window are different things

`Image` owns image data and provides operations intrinsic to an image, such as `Width()`, `Height()`, and `Pixel()`. `DrawImage(window, image, ...)` is a free function because it connects Image and Window.

Omitting a size draws at the original size. Supplying width and height smoothly scales it to that size.

## One step further

@code example2.cpp

## Extensions are ordinary C++ too

Using Image does not mean learning a new language. You include a header and use ordinary C++ objects and functions.

## Exercise — Draw at two sizes

Create a 120 × 80 Green image. Draw it at its original size and twice that size in one window.

@exercise exercise1_starter.cpp

### Hint

Use both the four-argument and six-argument forms of `DrawImage`.

@solution exercise1_solution.cpp

## Exercise — Check the size

Create a 64 × 48 image and print its Width and Height.

@exercise exercise2_starter.cpp

### Hint

Use `Print(image.Width(), " x ", image.Height());`.

@solution exercise2_solution.cpp

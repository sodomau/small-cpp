---
title: Loading and Saving
goal: Save image files and load them again.
---

## Connecting Image to files

`SaveImage` saves an Image to a file; `LoadImage` reads one. Supported formats such as PNG and JPEG depend on the Qt image plugins supplied with the application.

## Try it first

@code example1.cpp

## The filename chooses the format

An extension such as in `SaveImage(image, "picture.png")` chooses the saved format. Small reports a runtime error if a file cannot be opened or saved.

DrawImage composites the loaded image's alpha information.

## One step further

@code example2.cpp

## The basic Image workflow is complete

You can create or load an image, inspect or edit its pixels, draw it, and save it. These operations are ordinary C++ library APIs designed for use outside Small IDE too.

## Exercise — Save and read

Save a 50 × 50 Cyan image as `cyan.png`, then load it into a new Image.

@exercise exercise1_starter.cpp

### Hint

Use `Image loaded = LoadImage("cyan.png");`.

@solution exercise1_solution.cpp

## Exercise — Edit a file

Create and save an image, load it again, change (0, 0) to Magenta, and save under a different name.

@exercise exercise2_starter.cpp

### Hint

Using a second filename preserves the original file.

@solution exercise2_solution.cpp

## Share your finished program

Small Steps VII — Share Your Program shows how to make a Windows package. Include any image files your program loads with Add Files, then share the whole folder as a ZIP.

> Project-wide principles: see `PHILOSOPHY.md`.

# Small C++ API Design

## Keep classes small

A class contains only operations intrinsic to that abstraction. `Window` owns window lifecycle, its drawing surface, presentation, and input. `Image` owns image data, loading/saving, dimensions, and pixels.

## Relationships are free functions

When an operation connects independent abstractions, it lives outside both classes.

```cpp
draw_image(window, image, x, y);
```

not:

```cpp
window.draw_image(image, x, y);
image.Draw(window, x, y);
```

This avoids arbitrary ownership decisions and prevents central classes from accumulating knowledge of every future type.

> Classes represent things; free functions represent relationships between things.

## Extension dependency direction

Extensions may depend on Core. Core never depends on Extensions.

Thus Image may know `Window`, but `Window` and `small.h` never know `Image`. Future Plot, Sprite, Video, and similar extensions can follow the same rule without growing the core class interface.

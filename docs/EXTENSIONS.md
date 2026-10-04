# Small C++ Extensions

> Project-wide principles: see `PHILOSOPHY.md`.

## An extension is a self-contained folder

```text
extensions/
    image/
        extension.json
        include/
            small/
                image.h
        lib/
            small_image...
        examples/
        tutorial/
```

The IDE discovers `extensions/*/extension.json` at runtime. Nothing about Image is hard-coded into the extension registry or BuildController.

When source contains:

```cpp
#include <small/image.h>
```

the manifest identifies the owning extension. Small adds `extensions/image/include` as an include search path and links the library declared by the manifest.

Thus installation/removal is conceptually folder-level: copy an extension folder in; remove it to uninstall.

## Image API

Intrinsic operations are members; relationships are free functions:

```cpp
Image image("cat.png");
draw_image(window, image, 100, 100);
```

Core never depends on Image.

## Image completeness

Image supports in-memory creation, loading, saving, dimensions, rgb pixel access, alpha access, pixel editing, alpha-aware drawing, and scaled drawing.

`draw_image` uses a generic Core-internal RGBA blit bridge. The bridge accepts raw raster data and knows nothing about `Image`, preserving the dependency direction while avoiding per-pixel `Window::set_pixel()` calls.

The extension owns three examples and three tutorial lessons under its own folder. Installed extension content is discovered by the existing Examples and Tutorial browsers.

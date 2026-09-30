# Small C++ Guide

## Programming model

Small C++ is ordinary C++ compiled against the Small runtime. Beginners
use `SmallMain()` while the hidden entry point performs
`InitializeSmall() → SmallMain() → ShutdownSmall()`.

## Learning path

Values/variables → input/output → decisions → loops → functions →
String/Array → graphics/input/animation/sound → algorithms/files →
structs/classes/references → standard C++.

## Core philosophy

The API favors readability and a small surface. Implementation may be
complex when that complexity makes learner use simpler. Visual APIs
teach programming rather than full GUI-framework details.

## Extensions

Features outside the minimal core can be extensions. Image is the
reference extension. Extensions can provide headers, a library,
examples, and tutorials.

## Graduation

Small types are stepping stones. Later lessons reveal `std::string`,
`std::vector`, headers, namespaces, and ordinary `main()`. The goal is a
gradual reveal of C++, not a language switch.

## Visible control flow

The Window API deliberately keeps the program's main flow visible:

``` cpp
while (window.IsOpen())
{
    // input
    // update
    // draw
    window.Show();
}
```

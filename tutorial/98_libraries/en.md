---
title: Use Code Written by Others
part: libraries
part-title: Small Steps IX — Use External Libraries
goal: Use Code Written by Others
related-example: reference/console
---

## Before you start

An external library lets you use code written by others. However, **the Libraries menu, `//@` settings, `small.project`, and automatic package installation are Small C++ IDE features, not features of the C++ standard**. Other IDEs configure libraries in their own ways.

## Start with a small program

Run this program first. It does not need an external library yet.

@code example.cpp

Now try **fmt**, a library for formatting text. Open the example in the editor and replace it with this code.

```cpp
//@ {
//@     "libraries": ["fmt"]
//@ }

#include <fmt/format.h>

void small_main()
{
    print(fmt::format("Hello, {}!", "Small C++").c_str());
}
```

You can also choose **Tools → Libraries…**, search for `fmt`, check Use, and click OK. Selecting a library only saves its declaration. **Run** asks before installing missing packages. If you agree, Library Console shows installation output and the build follows. An installed package is used immediately. Installation needs an internet connection.

`#include <fmt/format.h>` and function calls are C++ code. The initial `//@` lines are ordinary comments to the compiler; Small IDE reads them as build settings.

## Libraries and packages

A library is code used by your program. A package is a unit for installing and managing files. The Library column contains pkg-config module names; Package contains the MSYS2 package providing each module. One package can provide several modules.

**Update List** refreshes the selection catalog only. It does not install or upgrade packages.

## Exercise — Greet someone else

Open the basic example, replace it with the fmt example, and change the greeting recipient to `friend`. Run it. The solution below is the basic C++ version with the same output. In the fmt version, change the second format argument instead of the whole string.

@exercise exercise_starter.cpp

### Hint

Replace `"Small C++"` in the fmt example with `"friend"`.

@solution exercise_solution.cpp

---
title: Choose and Use External Libraries
part: libraries
part-title: Small Steps IX — Use External Libraries
goal: Choose and Use External Libraries
related-example: reference/console
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Use Code Written by Others

### Before you start

An external library lets you use code written by others. However, **the Libraries menu, `//@` settings, `small.project`, and automatic package installation are Small C++ IDE features, not features of the C++ standard**. Other IDEs configure libraries in their own ways.

### Start with a small program

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

### Libraries and packages

A library is code used by your program. A package is a unit for installing and managing files. The Library column contains pkg-config module names; Package contains the MSYS2 package providing each module. One package can provide several modules.

**Update List** refreshes the selection catalog only. It does not install or upgrade packages.

## Where Are Library Settings Saved?

### A single file and a project

Save this basic program and select fmt through Tools → Libraries…. The editor adds `//@` settings at the beginning.

@code library_settings_example.cpp

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

**Only single-file mode** reads consecutive `//@` lines at the very beginning. A blank or ordinary line ends the block. Later `//@` lines are ordinary comments. This is a Small IDE rule.

### Projects use small.project

With a project open, Libraries saves your selection in `small.project` in the project folder. For example:

```json
{
    "version": 1,
    "libraries": ["fmt"]
}
```

If the file already exists, preserve its other options and edit only libraries. Project mode ignores individual cpp `//@` settings and uses **one small.project configuration**. libraries contains module names such as `fmt`, not long pacman package names.

Settings declare requirements only. Building on another computer checks installation there too. Include the initial settings when sharing a cpp, and include small.project when sharing a project.

## Exercise — Greet someone else

Open the basic example, replace it with the fmt example, and change the greeting recipient to `friend`. Run it. The solution below is the basic C++ version with the same output. In the fmt version, change the second format argument instead of the whole string.

@exercise exercise_starter.cpp

### Hint

Replace `"Small C++"` in the fmt example with `"friend"`.

@solution exercise_solution.cpp

## Try More (Optional)

## Exercise — Declarations and installation

Open the basic program and select fmt in Libraries. After OK, inspect the added comments. Then reopen Libraries and uncheck fmt. Unchecking changes the declaration; it does not uninstall the package. The solution program below prints the same greeting without a library.

@exercise library_settings_exercise_starter.cpp

### Hint

Use means this program requires the library. Installed describes the actual environment.

@solution library_settings_exercise_solution.cpp

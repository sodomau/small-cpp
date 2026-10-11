---
title: Where Are Library Settings Saved?
part: libraries
part-title: Small Steps IX — Use External Libraries
goal: Where Are Library Settings Saved?
related-example: reference/console
---

## A single file and a project

Save this basic program and select fmt through Tools → Libraries…. The editor adds `//@` settings at the beginning.

@code example.cpp

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

## Projects use small.project

With a project open, Libraries saves your selection in `small.project` in the project folder. For example:

```json
{
    "version": 1,
    "libraries": ["fmt"]
}
```

If the file already exists, preserve its other options and edit only libraries. Project mode ignores individual cpp `//@` settings and uses **one small.project configuration**. libraries contains module names such as `fmt`, not long pacman package names.

Settings declare requirements only. Building on another computer checks installation there too. Include the initial settings when sharing a cpp, and include small.project when sharing a project.

## Exercise — Declarations and installation

Open the basic program and select fmt in Libraries. After OK, inspect the added comments. Then reopen Libraries and uncheck fmt. Unchecking changes the declaration; it does not uninstall the package. The solution program below prints the same greeting without a library.

@exercise exercise_starter.cpp

### Hint

Use means this program requires the library. Installed describes the actual environment.

@solution exercise_solution.cpp

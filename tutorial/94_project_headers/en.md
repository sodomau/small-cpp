---
title: Give Functions a Header
part: projects
part-title: Small Steps VIII — Build with Several Files
goal: Put declarations in a header and definitions in a source file.
related-example: reference/console
---

## Keep introductions in one place

Previously we wrote a function declaration directly in `main.cpp`. A header keeps that introduction in one place when several files need it.

Right-click a blank area and choose **New Header File…** to create `greeting.h`. Keep the generated `#pragma once` line.

### greeting.h
```cpp
#pragma once

void SayHello();
```

### greeting.cpp
```cpp
#include "greeting.h"

void SayHello()
{
    Print("Hello from another file!");
}
```

### main.cpp
```cpp
#include "greeting.h"

void SmallMain()
{
    SayHello();
}
```

`#include "greeting.h"` reads that header into the current file. Use double quotes for a header in the same folder. The function body exists only in `greeting.cpp`. That file includes its own header too, so the compiler can check that the declaration matches the definition.

`#pragma once` prevents repeated inclusion of a header during the compilation of one source file. It is not a C++ standard feature, but Small C++'s compiler supports it. You can learn the standard alternative, include guards, later.

## Check the same behavior in one file

![The three-file Greeting project. main.cpp includes greeting.h.](project.png)

The following combines the same program into one file. **Open Example** opens this one-file version; it does not create the three project files automatically.

@code example.cpp

## Exercise — Check it yourself

Call SayHello twice in the one-file practice. Then get the same result in your project by changing only main.cpp.

@exercise exercise_starter.cpp

### Hint

Use the menus described above. The solution below is for the one-file practice. Apply the same change to the file with that job in your project.

@solution exercise_solution.cpp

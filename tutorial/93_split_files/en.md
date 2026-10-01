---
title: Split a Program into Two Files
part: projects
part-title: Small Steps VIII — Build with Several Files
goal: Move a function body to another source file.
related-example: reference/console
---

## Try it in one file first

@code example.cpp

We will move `SayHello` to another file. Continue in the `Greeting` project from the previous lesson.

## Create greeting.cpp

Right-click a blank area in the file list and choose **New Source File…**. Enter `greeting.cpp`. The new file opens in a tab. Put the following code in it.

### greeting.cpp
```cpp
void SayHello()
{
    Print("Hello from another file!");
}
```

Replace `main.cpp` with the following. Remove the body of `SayHello` from this file and add its declaration at the top.

### main.cpp
```cpp
void SayHello();

void SmallMain()
{
    SayHello();
}
```

`void SayHello();`, ending with a semicolon, introduces the function. The version with braces supplies its body. Choose **Run Project**: the result is unchanged.

Keep only one `SmallMain` in the whole project. Do not `#include` a `.cpp` file. The IDE compiles each included `.cpp` separately and links them together.

## Exercise — Check it yourself

Change the greeting in the one-file practice below. Then make the same change in your project's greeting.cpp. Close the main.cpp tab and try Run Project again.

@exercise exercise_starter.cpp

### Hint

Use the menus described above. The solution below is for the one-file practice. Apply the same change to the file with that job in your project.

@solution exercise_solution.cpp

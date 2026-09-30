# Getting Started

A packaged Small C++ release requires no separate Qt, MinGW, GDB, or IDE
installation.

## First program

``` cpp
void SmallMain()
{
    Print("Hello!");
}
```

Press **Run/F5**. Console programs open a console; graphical programs
open a Small Window.

## Learn

Open **Learn → Tutorial...**, choose a lesson, and press **Try This
Code**. The current Small Steps core pack supplies 88 Korean lessons.
**Settings → Tutorial Language** lists the languages supplied by the installed
content pack; the loader falls back to its default for missing translations.
Examples and API Reference are also under Learn.

## Debug

Click the editor gutter to set a breakpoint, then choose **Debug**. Use
Continue, Over, Into, Out, and Stop. Variables shows locals and user
globals. Breakpoints can be changed during a session.

## Growing into C++

Later lessons introduce structs/classes, references, the standard
library, headers/namespaces, and real `main()`:

``` cpp
#include <small.h>

int main(int argc, char** argv)
{
    Small::InitializeSmall(argc, argv);
    // program
    Small::ShutdownSmall();
    return 0;
}
```

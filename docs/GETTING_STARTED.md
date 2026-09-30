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

## Custom styles

Choose **Settings → Theme → Load Style Sheet...** to apply a UTF-8 `.qss`
file to the IDE and its Learn windows. The selected file is loaded again at
startup. After editing the file, choose **Reload Style Sheet**; changes are
not watched automatically. **Reset Style Sheet** removes the custom style
and restores the built-in appearance.

Light/Dark still selects syntax-highlighting and editor-gutter colors. QSS
can override widget colors and layout properties; it does not define C++
syntax-highlighting rules. Qt parses the QSS, so malformed or unsupported
rules may be ignored. A file read failure keeps the current style; a missing
file at startup leaves the built-in appearance and shows a status message.
Use absolute paths or Qt resource paths for images referenced with `url(...)`.

For example, save this as `my-style.qss` and load it:

```css
QPlainTextEdit { background-color: #f8fafc; color: #172033; }
QMenuBar, QToolBar { background-color: #e8eef8; }
QTabBar::tab:selected { background-color: #c5def5; }
```

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

# Window state and actions

`Window` exists before an operating-system window is opened.

Its title is an object property:

```cpp
Window window;
window.set_title("Pong");
window.open(800, 600);
```

`title()` and `set_title()` are valid before `open()`, while open, and after `close()`.
Changing the title while open immediately updates the native window.

`open()` remains an explicit action rather than constructor behavior.

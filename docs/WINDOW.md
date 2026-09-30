# Window state and actions

`Window` exists before an operating-system window is opened.

Its title is an object property:

```cpp
Window window;
window.SetTitle("Pong");
window.Open(800, 600);
```

`Title()` and `SetTitle()` are valid before `Open()`, while open, and after `Close()`.
Changing the title while open immediately updates the native window.

`Open()` remains an explicit action rather than constructor behavior.

# Building text values

`Print(...)` sends values to the console.

`Format(...)` uses the same argument style but returns a `String`:

```cpp
String text = Format("Score: ", score);
window.SetTitle("Level ", level, " - Score: ", score);
```

`String.Print(...)` was intentionally not added: printing is an output action, while formatting produces a String value. Keeping those concepts separate also lets Window titles and future APIs share the same formatting vocabulary.

# Building text values

`print(...)` sends values to the console.

`format(...)` uses the same argument style but returns a `String`:

```cpp
String text = format("Score: ", score);
window.set_title("Level ", level, " - Score: ", score);
```

`String.print(...)` was intentionally not added: printing is an output action, while formatting produces a String value. Keeping those concepts separate also lets Window titles and future APIs share the same formatting vocabulary.

When passing standard-library types such as `std::string`, write
`Small::format(...)` explicitly to distinguish it from C++20's `std::format`.
Small's function joins its arguments; `std::format` uses a format string.

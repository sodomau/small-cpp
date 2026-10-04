# Small C++ Naming Convention

## 1. Goals

Small C++ names should be easy to read for beginners while remaining natural in ordinary C/C++ code.

The convention follows a few simple principles:

- Types are visually distinct from values and operations.
- Function names describe actions.
- Variable names describe what a value means, not merely how it is represented.
- Names should remain readable even when they contain several words.
- Small C++ should look like clean C++, rather than a separate language or framework.

## 2. Summary

| Category | Convention | Examples |
|---|---|---|
| Class / type | `PascalCase` | `Window`, `String`, `Array`, `FileMode` |
| Function | `snake_case` | `print()`, `input_int()`, `load_image()` |
| Method | `snake_case` | `draw_text()`, `key_pressed()`, `write_int()` |
| Variable | `snake_case` | `file_name`, `play_time`, `frame_idx` |
| Boolean variable | Predicate-style `snake_case` | `is_open`, `has_alpha`, `can_write` |
| Enum value | `PascalCase` | `Key::Space`, `FileMode::ReadBinary` |
| Small C++ named constant | `PascalCase` | `Black`, `White`, `Red` |
| User `const` / `constexpr` variable | `snake_case` | `max_players`, `pi` |
| Entry point | `snake_case` | `small_main()` |

## 3. Types

Classes, structs, enums, and other user-visible types use **PascalCase**.

```cpp
String name;
Array<int> scores;
File file;
Window window;
Image image;
```

This makes types visually distinct and also allows the most natural object name to be used without conflict:

```cpp
Image image;
Window window;
Button button;
```

## 4. Functions and Methods

Functions and methods use **snake_case**.

Whenever possible, their names should be verbs or verb phrases describing the action being performed.

```cpp
print("Hello");
input_int("Age: ");
load_image("cat.jpg");

window.open(640, 480);
window.draw_text(20, 20, "Hello", White, 20);
file.write_int(score);
```

Prefer an explicit action over using a noun as if it were a verb.

```cpp
// Avoid
chart.legend();
chart.title("Result");

// Prefer
chart.show_legend();
chart.set_title("Result");
```

A slightly longer name is preferable when it makes the operation immediately understandable.

## 5. Variables

Variables use **snake_case** and should normally be nouns or noun phrases.

```cpp
int frame_count;
double play_time;
String file_name;
Image input_image;
int loaded_score;
```

Names should primarily describe the **meaning of the value**, rather than encode its C++ type.

Avoid systematic type prefixes such as:

```cpp
n_frame_count
f_weight
str_file_name
```

Prefer:

```cpp
frame_count
weight
file_name
```

## 6. Boolean Variables

Boolean variables are an exception to the general preference for noun-like variable names. A Boolean represents a proposition, so predicate-style names are preferred when they improve clarity.

```cpp
bool is_open;
bool is_restored;
bool has_alpha;
bool can_write;
bool needs_update;
```

This is preferred over encoding `bool` in the name:

```cpp
// Avoid when a clear predicate is available
bool b_restored;

// Prefer
bool is_restored;
```

Predicate names also read naturally at the point of use:

```cpp
if (is_restored[frame_idx]) {
    // ...
}
```

## 7. Raw Pointers

As a general rule, variable names should **not** encode C++ types. Raw pointers are a limited exception.

When distinguishing a pointer from the object it refers to improves clarity, the prefix `p_` may be used:

```cpp
Video video;
Video* p_video;
```

This is especially useful when the programmer conceptually thinks of the value as "a pointer to a video" rather than "the video itself," or when confusing the two could make the code harder to understand later.

The `p_` convention is **not** a general adoption of Hungarian notation. Do not extend it to systematic prefixes for every type:

```cpp
// Avoid
int n_count;
float f_weight;
bool b_valid;
String str_name;
```

The raw-pointer exception should be used only when it provides meaningful clarity.

Small C++ user code should in any case minimize direct use of raw pointers where a simpler and safer abstraction is available.

## 8. Semantic Qualifiers and Abbreviations

Suffixes or abbreviations are appropriate when they express **semantic information**, rather than merely restating a C++ type.

Examples:

```cpp
frame_idx
valid_mask
weight_map
blurred_p
lucky_p
```

Here, `idx` means that the value is an index. Likewise, if `_p` means *padded*, it distinguishes a padded image from its unpadded counterpart. These are meaningful properties of the data and are therefore appropriate parts of the name.

The guiding rule is:

> Encode meaning in names, not implementation details that are already obvious from the type.

## 9. Enum Values and Named Constants

Enum types use PascalCase, and their values also use PascalCase.

```cpp
Key::Space
Key::Enter
Key::Left
Key::Escape

FileMode::ReadBinary
FileMode::WriteBinary
```

Small C++ predefined named constants also use PascalCase:

```cpp
Black
White
Red
Green
Blue
```

Ordinary user-defined `const` or `constexpr` variables follow the normal variable convention and use snake_case:

```cpp
const int max_players = 4;
constexpr double pi = 3.141592;
```

## 10. Entry Point

The Small C++ entry point follows the same rule as other functions:

```cpp
void small_main()
{
    // ...
}
```

There is no special PascalCase exception for the entry point.

## 11. Example: File I/O

```cpp
void small_main()
{
    int level = input_int("Level: ");
    int score = input_int("Score: ");
    double play_time = input_real("Play time: ");

    File file;
    file.open("save.dat", FileMode::WriteBinary);
    file.write_int(level);
    file.write_int(score);
    file.write_real(play_time);
    file.close();

    print("Game saved.");

    file.open("save.dat", FileMode::ReadBinary);
    int loaded_level = file.read_int();
    int loaded_score = file.read_int();
    double loaded_time = file.read_real();
    file.close();

    print("Loaded level: ", loaded_level);
    print("Loaded score: ", loaded_score);
    print("Loaded play time: ", loaded_time);
}
```

## 12. Example: Window and Keyboard Input

```cpp
void small_main()
{
    Window window;
    window.open(640, 480);

    while (window.is_open())
    {
        if (window.key_pressed(Key::Space)) print("Space pressed");
        if (window.key_released(Key::Enter)) print("Enter released");
        if (window.key_down(Key::Left)) print("Left");
        if (window.key_down(Key::Right)) print("Right");

        if (window.key_down('A')) print("A is down");
        if (window.key_pressed('B')) print("B pressed");
        if (window.key_released('C')) print("C released");

        window.clear(Black);
        window.draw_text(20, 20, "Press keys", White, 20);
        window.show();
    }
}
```

## 13. Rationale

Small C++ uses `PascalCase` for types and `snake_case` for functions, methods, and variables because this combination provides several useful properties:

- Multi-word identifiers have explicit and highly visible word boundaries.
- Types remain immediately distinguishable from objects and operations.
- The style blends naturally with the C/C++ standard-library tradition, including names such as `push_back` and `lower_bound`.
- It is also familiar to Python programmers, whose conventional style similarly uses PascalCase for classes and snake_case for functions and variables.
- Most importantly, the convention keeps Small C++ looking like clean C++ rather than a separate programming language.

Naming rules should serve readability rather than become an end in themselves. When a special naming form conveys genuine semantic information, clarity takes priority over mechanical uniformity.

## Migration of existing Small C++ programs

This convention replaces the previous PascalCase function and method names.
There are no compatibility aliases: update existing source before rebuilding.

| Previous name | Current name |
|---|---|
| `SmallMain` | `small_main` |
| `Print`, `InputInt` | `print`, `input_int` |
| `Window.Open`, `Window.KeyPressed` | `Window.open`, `Window.key_pressed` |
| `String.Length`, `String.Substring` | `String.length`, `String.substring` |
| `RGB`, `LoadImage`, `SaveImage` | `rgb`, `load_image`, `save_image` |

Types, enum values, and Small's named color constants retain their names.
The IDE's implementation identifiers are outside this convention.

When passing `std::string` or other standard-library types to Small's text
builder, write `Small::format(...)` to distinguish it from `std::format`.

---
title: Print to the Screen
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Print to the Screen
related-example: reference/console
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Showing text on the screen

### What you will learn

A **program** tells a computer what to do. The written instructions are **code**; asking the computer to carry them out is **running** the program. Today we will display a greeting.

### Try it

@code example.cpp

Open the code with **Try This Code**, then press **Run or F5**. The text appears in a console window.

A **string** is a value made of characters in order. The double quotes in `"Hello!"` mark its beginning and end. A **function** groups instructions under a name. `print` is a function that produces output; `print("Hello!");` passes it a greeting and calls it.

small_main is the function where we write our instructions. For now, keep the surrounding structure and change only `print` inside `{ }`. Keep the `;` at the end of the statement too.

Expected output:

```text
Hello!
```

## Running from top to bottom

### What you will learn

When you write several instructions, they run from top to bottom. `print` moves to a new line after producing its output.

### Try it

@code lines_example.cpp

After the first `print` finishes, the second one runs. Swapping the two lines swaps the order of the output.

In code, everything from `//` to the end of that line is a **comment**. It is a note for people and does not run. Put // before the first instruction and see what changes.

Expected output:

```text
Hello!
Small C++
```

## Including quotes and newlines

### What you will learn

Use **escape sequences** beginning with a backslash to include special characters in a string.

### Try it

@code escape_example.cpp

`\n` represents a newline, `\"` one double quote, and `\\` one backslash. Although written with two symbols in code, each represents one character.

`""` is an empty string; `" "` contains one space. Even when `print` outputs an empty string, it adds a newline at the end.

Expected output:

```text
Hello
Small
"Hi"
```

## Exercise

Print your own name instead of "Hello!".

@exercise exercise_starter.cpp

### Hint

Change only the text inside the double quotes. `print` starts with a lowercase p.

@solution exercise_solution.cpp

## Try More (Optional)

## Exercise

Print your name, something you like, and something you want to make on three lines.

@exercise lines_exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution lines_exercise_solution.cpp

## Exercise

Print A and B on different lines with a single `print` call.

@exercise escape_exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution escape_exercise_solution.cpp

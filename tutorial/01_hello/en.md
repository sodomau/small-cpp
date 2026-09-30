---
title: Showing text on the screen
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Print your own name instead of "Hello!".
related-example: reference/console
---

## What you will learn

A **program** tells a computer what to do. The written instructions are **code**; asking the computer to carry them out is **running** the program. Today we will display a greeting.

## Try it

@code example.cpp

Open the code with **Try This Code**, then press **Run or F5**. The text appears in a console window.

A **string** is a value made of characters in order. The double quotes in `"Hello!"` mark its beginning and end. A **function** groups instructions under a name. Print is a function that produces output; `Print("Hello!");` passes it a greeting and calls it.

SmallMain is the function where we write our instructions. For now, keep the surrounding structure and change only Print inside `{ }`. Keep the `;` at the end of the statement too.

Expected output:

```text
Hello!
```

## Exercise

Print your own name instead of "Hello!".

@exercise exercise_starter.cpp

### Hint

Change only the text inside the double quotes. Print starts with an uppercase P.

@solution exercise_solution.cpp

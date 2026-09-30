---
title: Including quotes and newlines
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Print A and B on different lines with a single Print call.
related-example: reference/console
---

## What you will learn

Use **escape sequences** beginning with a backslash to include special characters in a string.

## Try it

@code example.cpp

`\n` represents a newline, `\"` one double quote, and `\\` one backslash. Although written with two symbols in code, each represents one character.

`""` is an empty string; `" "` contains one space. Even when Print outputs an empty string, it adds a newline at the end.

Expected output:

```text
Hello
Small
"Hi"
```

## Exercise

Print A and B on different lines with a single Print call.

@exercise exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution exercise_solution.cpp

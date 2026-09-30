---
title: Joining strings
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Join Good, one space, and morning, then print the result.
related-example: reference/console
---

## What you will learn

For String values, `+` performs **concatenation** rather than numeric addition. The joined result is also a String value.

## Try it

@code example.cpp

`text.Length()` returns the length of text. The dot means you are using an operation belonging to text. Spaces count too.

Length is counted in **bytes**, a unit of data size. Each character in this English example is one byte. A Korean character in UTF-8 uses several bytes, so byte length may differ from character count.

Expected output:

```text
Small C++
9
```

## Exercise

Join Good, one space, and morning, then print the result.

@exercise exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution exercise_solution.cpp

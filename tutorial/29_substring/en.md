---
title: Taking part of a string
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Take Sm, the first two characters of Small.
related-example: reference/console
---

## What you will learn

A **substring** is a consecutive part of a string. Pass Substring a starting position and the length to take.

## Try it

@code example.cpp

Position 1 is m. Taking three characters from there gives mal. Omitting the length, as in `Substring(1)`, takes everything from position 1 to the end.

In a string of length 5, character positions are 0–4. Stay within those bounds when reading a character with brackets.

Expected output:

```text
mal
```

## Exercise

Take Sm, the first two characters of Small.

@exercise exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution exercise_solution.cpp

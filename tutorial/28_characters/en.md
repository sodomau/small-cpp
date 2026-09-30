---
title: Taking out one character
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Print m, the second character of Small.
related-example: reference/console
---

## What you will learn

A **character** is a single letter or symbol. **char** is a type for character values. Write one English letter with single quotes, such as `'A'`.

## Try it

@code example.cpp

`word[0]` reads the character at the first position. Positions start at 0. The valid positions in Small are 0 through 4.

`7` is an integer, `'7'` a character, and `"7"` a string. char holds one byte, so a whole Korean UTF-8 character cannot fit in one char. Practice with English letters here.

Expected output:

```text
A
S
```

## Exercise

Print m, the second character of Small.

@exercise exercise_starter.cpp

### Hint

The second position has index 1.

@solution exercise_solution.cpp

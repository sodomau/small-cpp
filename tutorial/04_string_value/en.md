---
title: Work with Strings
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Work with Strings
related-example: reference/console
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Storing strings too

### What you will learn

You can store names and sentences in variables too. A **string** is a kind of value; **String** is the name of the Small type used to store it.

### Try it

@code example.cpp

`print("Hello, ", name);` prints the greeting followed by the value of name. It does not print the comma or automatically add a space. Put any spaces you need inside the double quotes.

`"123"` is a string of characters. It is a different kind of value from the integer 123 used in numeric calculations.

Expected output:

```text
Hello, Alex
```

## Joining strings

### What you will learn

For String values, `+` performs **concatenation** rather than numeric addition. The joined result is also a String value.

### Try it

@code string_join_example.cpp

`text.length()` returns the length of text. The dot means you are using an operation belonging to text. Spaces count too.

`length` is counted in **bytes**, a unit of data size. Each character in this English example is one byte. A Korean character in UTF-8 uses several bytes, so byte length may differ from character count.

Expected output:

```text
Small C++
9
```

## Taking out one character

### What you will learn

A **character** is a single letter or symbol. **char** is a type for character values. Write one English letter with single quotes, such as `'A'`.

### Try it

@code characters_example.cpp

`word[0]` reads the character at the first position. Positions start at 0. The valid positions in Small are 0 through 4.

`7` is an integer, `'7'` a character, and `"7"` a string. char holds one byte, so a whole Korean UTF-8 character cannot fit in one char. Practice with English letters here.

Expected output:

```text
A
S
```

## Taking part of a string

### What you will learn

A **substring** is a consecutive part of a string. Pass `substring` a starting position and the length to take.

### Try it

@code substring_example.cpp

Position 1 is m. Taking three characters from there gives mal. Omitting the length, as in `substring(1)`, takes everything from position 1 to the end.

In a string of length 5, character positions are 0–4. Stay within those bounds when reading a character with brackets.

Expected output:

```text
mal
```

## Exercise

Store your favorite food's name in food and print it after Food:.

@exercise exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution exercise_solution.cpp

## Try More (Optional)

## Exercise

Join Good, one space, and morning, then print the result.

@exercise string_join_exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution string_join_exercise_solution.cpp

## Exercise

Print m, the second character of Small.

@exercise characters_exercise_starter.cpp

### Hint

The second position has index 1.

@solution characters_exercise_solution.cpp

## Exercise

Take Sm, the first two characters of Small.

@exercise substring_exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution substring_exercise_solution.cpp

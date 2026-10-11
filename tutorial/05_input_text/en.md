---
title: Read Input
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Read Input
related-example: reference/console
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Asking for a name while running

### What you will learn

`input` means receiving a value from outside the program. The `input` function returns a line typed on the keyboard as a string.

### Try it

@code example.cpp

After Run, type Alex in the console and press Enter. The program is not broken while `input` waits. When you finish, it stores the string in name and runs the next line.

You can also put a prompt inside the parentheses, as in `input("Name: ")`.

Expected output (excluding input prompts):

```text
Hello, Alex
```

## Calculating with an entered number

### What you will learn

input_int reads the input as an **integer** and returns it. Use it differently from `input`, which returns a string.

### Try it

@code input_int_example.cpp

Type 10 in the console and press Enter. Adding 1 to the integer 10 produces 11. Enter one integer per line. If you enter text that is not a number, a prompt asks you to try again.

Expected output (excluding input prompts):

```text
11
```

## Making a small calculator

### What you will learn

input_real reads a number with a fractional part as a double. Connecting **input → calculation → output** makes a calculator.

### Try it

@code input_real_example.cpp

Type 2.5 and press Enter, then type 3.5 and press Enter. The function is called twice, so you enter two values. The program stores them in a and b and prints their sum.

Expected output (excluding input prompts):

```text
6
```

## Exercise

Read a name and print it after Nice to meet you,.

@exercise exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution exercise_solution.cpp

## Try More (Optional)

## Exercise

Read one number and print twice its value. Entering 7 should produce 14.

@exercise input_int_exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution input_int_exercise_solution.cpp

## Exercise

Read a width and height and print their area. Entering 3.5 and 2 gives 7.

@exercise input_real_exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution input_real_exercise_solution.cpp

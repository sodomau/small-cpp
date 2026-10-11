---
title: Repeat Instructions
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Repeat Instructions
related-example: reference/console
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Repeating the same instructions

### What you will learn

A **loop** runs a block of code several times. for specifies the initial setup, the condition for continuing, and the update to the next value.

### Try it

@code example.cpp

i starts at 1. If the condition is true, the program prints, increases i by 1, and checks again. After printing 3, i becomes 4 and the false condition ends the loop. i is a variable name we chose.

Expected output:

```text
1
2
3
```

## Repeating while a condition holds

### What you will learn

**while** repeats the code inside braces while its condition is true. It checks the condition before every iteration.

### Try it

@code while_example.cpp

The loop ends when count becomes 0. If it starts at 0, nothing is printed. Removing the line that decreases count makes the loop run forever; use the IDE's Stop button in that case.

for is convenient when counting iterations; while is convenient when waiting for a condition to change.

Expected output:

```text
3
2
1
```

## Stopping or skipping an iteration

### What you will learn

**break** ends the innermost loop. **continue** skips the rest of the current iteration and moves to the next one.

### Try it

@code loop_control_example.cpp

At 2, `print` is skipped. for increases i and checks the next condition. At 4, the entire loop ends, so neither 4 nor 5 is printed.

Expected output:

```text
1
3
```

## Drawing several rows of stars

### What you will learn

You can put a loop inside another loop. The outer loop counts rows; the inner loop counts the stars in each row.

### Try it

@code nested_loops_example.cpp

`write` does not move to a new line after output. **print()** moves to a new line without printing content. The program therefore prints three adjacent stars and then a newline, twice.

Expected output:

```text
***
***
```

## Exercise

Change the program to print 1 through 5.

@exercise exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution exercise_solution.cpp

## Try More (Optional)

## Exercise

Print backwards from 5 to 1.

@exercise while_exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution while_exercise_solution.cpp

## Exercise

Skip 3 instead of 2, and stop at 5.

@exercise loop_control_exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution loop_control_exercise_solution.cpp

## Exercise

Draw three rows with four stars each.

@exercise nested_loops_exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution nested_loops_exercise_solution.cpp

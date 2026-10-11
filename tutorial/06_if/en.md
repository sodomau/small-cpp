---
title: Make Decisions
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Make Decisions
related-example: reference/console
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Running only when a condition holds

### What you will learn

A **condition** is an expression that can be true or false. if is a **conditional statement** that runs the code inside its braces only when the condition is true.

### Try it

@code example.cpp

`score >= 60` asks whether the score is at least 60. With 80, it is true and prints Pass. Change it to 50: Pass is skipped and only Done is printed.

`>` means greater than, `<` less than, `>=` at least, and `<=` at most. Do not put a ; after the closing brace of if.

Expected output:

```text
Pass
Done
```

## Doing something else when a condition is false

### What you will learn

**else** holds the instructions to run when the if condition is false. It chooses one of two branches.

### Try it

@code else_example.cpp

Use `==` to compare for equality. It is different from `=`, which assigns a value. `!=` compares whether values differ. Changing answer to 5 runs only the else branch.

Expected output:

```text
Correct
```

## Choosing one of three branches

### What you will learn

For three or more choices, connect conditions with **else if**. They are checked from top to bottom, and only the first matching branch runs.

### Try it

@code else_if_example.cpp

0 is neither positive nor negative, so it reaches the final else. Several independent if statements check their conditions separately, so more than one branch may run.

Expected output:

```text
Zero
```

## Remembering true and false

### What you will learn

**bool** is a type that stores true or false. It remembers states such as whether you are ready or whether a game is over.

### Try it

@code bool_example.cpp

You can put a bool variable directly in if. Small's `print` displays true as 1 and false as 0. You can also store a comparison result, as in `bool passed = score >= 60;`.

Expected output:

```text
Start
1
```

## Combining two conditions

### What you will learn

`&&` means **both conditions are true**, `||` means **at least one is true**, and `!` reverses true and false.

### Try it

@code logic_example.cpp

Check whether the age is at least 13 and at most 19. Try 12, 13, 19, and 20 to check the boundaries.

`!ready` asks whether you are not ready. && skips the right side if the left is false; || skips it if the left is true.

Expected output:

```text
Teen
```

## Exercise

Print Positive only when number is greater than 0. Test with 3 first.

@exercise exercise_starter.cpp

### Hint

Also change 3 to 0 and -1. Those cases should produce no output.

@solution exercise_solution.cpp

## Try More (Optional)

## Exercise

Print Open when the password equals 1234 and Locked otherwise. Test with 1111.

@exercise else_exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution else_exercise_solution.cpp

## Exercise

Change number to -2 and check which branch runs.

@exercise else_if_exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution else_if_exercise_solution.cpp

## Exercise

Change is_ready to false and check how the output changes.

@exercise bool_exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution bool_exercise_solution.cpp

## Exercise

Print Outside when the age is below 13 or above 19. Test with 20.

@exercise logic_exercise_starter.cpp

### Hint

Use || between the two conditions.

@solution logic_exercise_solution.cpp

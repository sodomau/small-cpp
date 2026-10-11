---
title: Variables and Constants
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Variables and Constants
related-example: reference/console
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Giving a value a name

### What you will learn

A **variable** is a named place to store a value. Let us remember a score under the name score.

### Try it

@code example.cpp

`int score = 10;` creates a variable named score and gives it the initial value 10. **int is an integer type**. A type describes the kind of value stored; integers such as 0, 10, and -3 have no fractional part.

Creating a variable is called **declaration**; giving it its first value is **initialization**. For now, always give a variable a value when you create it. `print(score);` prints the stored value, rather than the letters score.

Expected output:

```text
10
```

## Changing a stored value

### What you will learn

You can keep a variable's name and change the value inside it. Storing a new value is called **assignment**.

### Try it

@code assignment_example.cpp

Running `score = 20;` replaces the previous value 10 with 20. The variable already exists, so do not write int again. `=` puts the value on the right into the variable on the left.

Expected output:

```text
10
20
```

## Calculating with a remembered value

### What you will learn

You can use stored values in calculations. Store the result again to increase a score.

### Try it

@code update_example.cpp

`score = score + 5;` first reads the current value 10, adds 5, then stores the result 15 in score. It does not mean that both sides are equal, as a mathematical equation would.

Running only `print(score + 5);` displays the calculated result but does not change score itself.

Expected output:

```text
15
```

## Storing values with fractional parts

### What you will learn

Lengths and times may need fractional parts. **double** is a type for these numbers. Choose int for whole-number counts and double for values that need a fractional part.

### Try it

@code double_example.cpp

A variable's type is chosen when it is created. Assigning a fractional number to an int later does not turn it into a double variable.

double cannot store every number with unlimited precision, but for now we will start with simple lengths and times.

Expected output:

```text
1.45
```

## Naming a value that will not change

### What you will learn

**const** means the initial value will not be changed later. Use it to name a fixed value such as a game's target score.

### Try it

@code constants_example.cpp

Assigning a different value to goal_score later causes a compilation error.

In this course, start names with an English letter and use letters, digits, and underscores. Do not include spaces. score and Score are different names. C++ keywords such as int and if cannot be names.

Expected output:

```text
20
```

## Shorter ways to update a value

### What you will learn

You can shorten commonly used calculations and assignments. For int or double, `score += 5;` makes the same update as `score = score + 5;`.

### Try it

@code short_updates_example.cpp

`++` increases by 1; `--` decreases by 1. At first, use them as separate statements as in the example. `-=`, `*=`, and `/=` work similarly. Integers also support `%=`. Integer /= still performs integer division.

Expected output:

```text
14
```

## Exercise

Store 10 in an int variable named age and print it.

@exercise exercise_starter.cpp

### Hint

Use the name age instead of score.

@solution exercise_solution.cpp

## Try More (Optional)

## Exercise

Set the score to 3, then change it to 8, printing it each time.

@exercise assignment_exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution assignment_exercise_solution.cpp

## Exercise

Create lives with the value 3, reduce it by 1, and print it.

@exercise update_exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution update_exercise_solution.cpp

## Exercise

Store a running time of 12.5 in a variable named seconds and print it.

@exercise double_exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution double_exercise_solution.cpp

## Exercise

Set a goal of 200 and print how much more is needed from a current score of 80.

@exercise constants_exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution constants_exercise_solution.cpp

## Exercise

Start the score at 10, double it, then increase it by 1 and print it.

@exercise short_updates_exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution short_updates_exercise_solution.cpp

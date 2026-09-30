---
title: Naming a task you created
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Call Greet three times.
related-example: reference/console
---

## What you will learn

A **function** groups instructions under a name. You have used Print; now you will create a function named Greet yourself.

## Try it

@code example.cpp

The upper section is the **definition** of what Greet does. `Greet();` below is a **call** that asks it to do that work. A definition alone does not run. Calling it from SmallMain goes to Greet, then returns after it finishes.

**void** means the function does not return a result value to its caller. It can still produce output. Empty () means that no values are passed in.

Expected output:

```text
Hello!
Hello!
```

## Exercise

Call Greet three times.

@exercise exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution exercise_solution.cpp

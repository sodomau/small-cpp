---
title: Create Functions
part: basics
part-title: Small Steps I — Creating with Text and Numbers
goal: Create Functions
related-example: reference/console
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Naming a task you created

### What you will learn

A **function** groups instructions under a name. You have used `print`; now you will create a function named greet yourself.

### Try it

@code example.cpp

The upper section is the **definition** of what greet does. `greet();` below is a **call** that asks it to do that work. A definition alone does not run. Calling it from small_main goes to greet, then returns after it finishes.

**void** means the function does not return a result value to its caller. It can still produce output. Empty () means that no values are passed in.

Expected output:

```text
Hello!
Hello!
```

## Passing values to a function

### What you will learn

Passing a value lets a function do the same work with different values. A variable that holds a received value is a **parameter**.

### Try it

@code parameters_example.cpp

number starts at 3 in the first call and 5 in the second. The values 3 and 5 supplied in the calls are **arguments**. number is a variable used while this function runs.

Expected output:

```text
6
10
```

## Receiving a function's result

### What you will learn

A **return value** is a value sent back to the caller. return sends the value back and ends that function's execution.

### Try it

@code return_value_example.cpp

The int at the beginning means the result is an integer. The program stores the 16 returned by square(4) in result. The function handles calculation; small_main handles output.

input_int was also a function that returns a value: the integer it read.

Expected output:

```text
16
```

## Using separate variables inside a function

### What you will learn

A **local variable** created inside a function is used within its scope. A parameter passed by value also holds a value separately from the original.

### Try it

@code scope_example.cpp

number receives a copy of score's value, 10. Only number changes, so score is still 10 when the function returns.

Ordinary local variables reach the end of their lifetime when their scope ends. They do not automatically remember a value for the next call. Later lessons on references show how to change the original.

Expected output:

```text
11
10
```

## Exercise

Call greet three times.

@exercise exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution exercise_solution.cpp

## Try More (Optional)

## Exercise

Pass 7 and 10 to show_double and print the results in order.

@exercise parameters_exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution parameters_exercise_solution.cpp

## Exercise

Receive and print the result of square(6).

@exercise return_value_exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution return_value_exercise_solution.cpp

## Exercise

Predict the two outputs when score starts at 20, then check your prediction.

@exercise scope_exercise_starter.cpp

### Hint

Change the parts of the example that you need.

@solution scope_exercise_solution.cpp

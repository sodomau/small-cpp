---
title: Running a function when it is time
part: making_things
part-title: Small Steps II — Making Things
goal: Run a function when it is time.
related-example: reference/timer
---

## What you will learn

An **event** is something a program responds to. A **callback** is a function entrusted to run when that event occurs. Use Timer to run a function about once a second.

## Try it

@code example1.cpp

on_timer has no () in start(1.0, on_timer) because you are specifying the function to call later, rather than calling it now.

ticks, outside all functions, is a **global variable** shared by several functions. Each callback adds 1. Timer events are processed during `sleep` too; `stop` stops the timer. Scheduling does not guarantee an exact number of calls.

## Exercise

Make a callback run every 0.5 seconds, increasing count by 1 and printing it. Call `stop` on the Timer after about 2.2 seconds.

@exercise exercise1_starter.cpp

### Hint

Use `timer.start(0.5, on_timer)` and increase count in the callback.

@solution exercise1_solution.cpp

---
title: Use Timers
part: making_things
part-title: Small Steps II — Making Things
goal: Use Timers
related-example: reference/timer
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Running a function when it is time

### What you will learn

An **event** is something a program responds to. A **callback** is a function entrusted to run when that event occurs. Use Timer to run a function about once a second.

### Try it

@code example1.cpp

on_timer has no () in start(1.0, on_timer) because you are specifying the function to call later, rather than calling it now.

ticks, outside all functions, is a **global variable** shared by several functions. Each callback adds 1. Timer events are processed during `sleep` too; `stop` stops the timer. Scheduling does not guarantee an exact number of calls.

## Displaying a timer's value

### What you will learn

A callback can change a value while the window loop reads that value and draws it.

### Try it

@code events_2_example2.cpp

on_second increases the global seconds, and draw_text displays its current value. `format` returns a String joining text and values. Unlike `print`, it does not produce output itself.

Timer is not a separate computation thread. Callbacks run when `show` or `sleep` processes events, so a long calculation may delay them. Use StopWatch for accurate elapsed-time measurement.

## Exercise

Make a callback run every 0.5 seconds, increasing count by 1 and printing it. Call `stop` on the Timer after about 2.2 seconds.

@exercise exercise1_starter.cpp

### Hint

Use `timer.start(0.5, on_timer)` and increase count in the callback.

@solution exercise1_solution.cpp

## Try More (Optional)

## Exercise

Have a Timer callback increase level by 1 each second. In the Window loop, show the current level in the title with `set_title("Level ", level)`.

@exercise events_2_exercise2_starter.cpp

### Hint

Change only the global int level in the callback and update the Window title in the main loop.

@solution events_2_exercise2_solution.cpp

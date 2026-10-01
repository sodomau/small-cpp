---
title: Measuring elapsed time
part: making_things
part-title: Small Steps II — Making Things
goal: Measure elapsed time.
related-example: reference/stopwatch
---

## What you will learn

**StopWatch** measures elapsed time. It starts when you create the object, and Elapsed reports the seconds that have passed.

## Try it

@code example1.cpp

After Sleep(1.0), the result is about 1 second. After Reset and Sleep(0.5), it is about 0.5 seconds. Reading the watch does not reset it to zero; Reset starts the measurement again.

It is normal for the execution environment to make the results differ from exactly 1.000 or 0.500.

## Exercise

Create a StopWatch and print Elapsed after Sleep(2.0). A result other than exactly 2.000... is normal.

@exercise exercise1_starter.cpp

### Hint

StopWatch starts when created, so it needs no separate Start call.

@solution exercise1_solution.cpp

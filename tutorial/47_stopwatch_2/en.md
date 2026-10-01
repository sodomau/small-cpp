---
title: Moving according to actual time
part: making_things
part-title: Small Steps II — Making Things
goal: Move according to actual time.
related-example: reference/stopwatch
---

## What you will learn

Distance = speed × time. Choosing a speed per second and moving by the elapsed time keeps movement consistent even when loop rates differ.

## Try it

@code example2.cpp

dt stores the time since the previous iteration. Read it with Elapsed, Reset the watch, and add `speed * dt` to the position.

At 200 pixels per second, the object moves 2 pixels in 0.01 seconds and 4 in 0.02 seconds. dt is not new syntax. Change speed to 100 and compare.

## Exercise

Update the vertically moving ball from lesson 44 to use dt and a speed of 150 pixels per second.

@exercise exercise2_starter.cpp

### Hint

Each loop, use `double dt = watch.Elapsed(); watch.Reset();`, then move with `y = y + speed * dt;`.

@solution exercise2_solution.cpp

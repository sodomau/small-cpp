---
title: Animate with Time
part: making_things
part-title: Small Steps II — Making Things
goal: Animate with Time
related-example: programs/bouncing_ball
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Changing position and drawing again

### What you will learn

**Animation** displays pictures in succession while changing their state a little at a time. Here, we change the circle's x position.

### Try it

@code example1.cpp

Each iteration increases x by 2, clears the background, and draws and displays the circle. When it passes the right edge, x returns to 0.

sleep(0.01) waits about 0.01 seconds. Check that the circle moves right and reappears on the left.

## Bouncing by changing direction

### What you will learn

The sign of a speed value can represent direction: positive moves right and negative moves left.

### Try it

@code animation_2_example2.cpp

At a boundary, `speed = -speed;` reverses the sign. Account for the radius of 20 so the center stays between 20 and 620.

This speed is currently distance per iteration. Computers may run loops at different rates, so next we will use elapsed time.

## Measuring elapsed time

### What you will learn

**StopWatch** measures elapsed time. It starts when you create the object, and `elapsed` reports the seconds that have passed.

### Try it

@code stopwatch_1_example1.cpp

After sleep(1.0), the result is about 1 second. After `reset` and sleep(0.5), it is about 0.5 seconds. Reading the watch does not reset it to zero; `reset` starts the measurement again.

It is normal for the execution environment to make the results differ from exactly 1.000 or 0.500.

## Moving according to actual time

### What you will learn

Distance = speed × time. Choosing a speed per second and moving by the elapsed time keeps movement consistent even when loop rates differ.

### Try it

@code stopwatch_2_example2.cpp

dt stores the time since the previous iteration. Read it with `elapsed`, then `reset` the watch, and add `speed * dt` to the position.

At 200 pixels per second, the object moves 2 pixels in 0.01 seconds and 4 in 0.02 seconds. dt is not new syntax. Change speed to 100 and compare.

## Exercise

Place the circle at x=320 in the center of the screen and move it along y. Reverse its direction at the top and bottom edges.

@exercise exercise1_starter.cpp

### Hint

Create y and speed. Reverse the sign of speed when `y > 460 || y < 20`.

@solution exercise1_solution.cpp

## Try More (Optional)

## Exercise

Move two balls with different x positions and speeds on one screen. Make both restart from the left after passing the right edge.

@exercise animation_2_exercise2_starter.cpp

### Hint

Create x1, x2, speed1, and speed2 separately.

@solution animation_2_exercise2_solution.cpp

## Exercise

Create a StopWatch and print `elapsed` after sleep(2.0). A result other than exactly 2.000... is normal.

@exercise stopwatch_1_exercise1_starter.cpp

### Hint

StopWatch starts when created, so it needs no separate `start` call.

@solution stopwatch_1_exercise1_solution.cpp

## Exercise

Update the vertically moving ball from the earlier animation example to use dt and a speed of 150 pixels per second.

@exercise stopwatch_2_exercise2_starter.cpp

### Hint

Each loop, use `double dt = watch.elapsed(); watch.reset();`, then move with `y = y + speed * dt;`.

@solution stopwatch_2_exercise2_solution.cpp

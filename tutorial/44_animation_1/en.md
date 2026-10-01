---
title: Changing position and drawing again
part: making_things
part-title: Small Steps II — Making Things
goal: Change a position and draw again.
related-example: programs/bouncing_ball
---

## What you will learn

**Animation** displays pictures in succession while changing their state a little at a time. Here, we change the circle's x position.

## Try it

@code example1.cpp

Each iteration increases x by 2, clears the background, and draws and displays the circle. When it passes the right edge, x returns to 0.

Sleep(0.01) waits about 0.01 seconds. Check that the circle moves right and reappears on the left.

## Exercise

Place the circle at x=320 in the center of the screen and move it along y. Reverse its direction at the top and bottom edges.

@exercise exercise1_starter.cpp

### Hint

Create y and speed. Reverse the sign of speed when `y > 460 || y < 20`.

@solution exercise1_solution.cpp

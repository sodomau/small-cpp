---
title: Bouncing by changing direction
part: making_things
part-title: Part II — Making Things
goal: Bounce by changing direction.
related-example: programs/bouncing_ball
---

## What you will learn

The sign of a speed value can represent direction: positive moves right and negative moves left.

## Try it

@code example2.cpp

At a boundary, `speed = -speed;` reverses the sign. Account for the radius of 20 so the center stays between 20 and 620.

This speed is currently distance per iteration. Computers may run loops at different rates, so next we will use elapsed time.

## Exercise

Move two balls with different x positions and speeds on one screen. Make both restart from the left after passing the right edge.

@exercise exercise2_starter.cpp

### Hint

Create x1, x2, speed1, and speed2 separately.

@solution exercise2_solution.cpp

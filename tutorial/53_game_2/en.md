---
title: Adding a score to a game
part: making_things
part-title: Small Steps II — Making Things
goal: Add a score to a game.
related-example: programs/pong
---

## What you will learn

**Game rules** determine how state changes when an event occurs. Increase the score only when the ball is caught.

## Try it

@code example2.cpp

Move the paddle with the left and right arrow keys. When the ball touches the paddle's range, it bounces and score increases by 1. SetTitle displays the current score in the window title.

After a miss, only the ball returns to its starting position. Test both hits and misses. Diagnose problems by separating position updates, conditions, and score changes.

## Exercise

Move the starter's paddle with the left and right arrow keys. Increase score by 1 only when the ball hits it, and show it with `window.SetTitle("Score: ", score)`. Moving the paddle aside and missing must not increase the score. Collision detection is provided in the starter.

@exercise exercise2_starter.cpp

### Hint

Create score with value 0 outside the loop, and increase it inside the collision if.

@solution exercise2_solution.cpp

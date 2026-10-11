---
title: Make a Small Game
part: making_things
part-title: Small Steps II — Making Things
goal: Make a Small Game
related-example: programs/pong
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Combining what you learned into a small game

### What you will learn

A **game** receives input, changes its state, and draws that state. This lesson is an assembly activity rather than new syntax.

### Try it

@code example1.cpp

Run the example and move the paddle with the up and down arrow keys. The code reads time and input, updates positions, handles collisions, then draws.

A collision check asks whether objects touch. After crossing a wall, the program corrects the position to the boundary as well as reversing direction. Start by finding the paddle movement instead of changing everything at once.

## Adding a score to a game

### What you will learn

**Game rules** determine how state changes when an event occurs. Increase the score only when the ball is caught.

### Try it

@code game_2_example2.cpp

Move the paddle with the left and right arrow keys. When the ball touches the paddle's range, it bounces and score increases by 1. set_title displays the current score in the window title.

After a miss, only the ball returns to its starting position. Test both hits and misses. Diagnose problems by separating position updates, conditions, and score changes.

## Exercise

The starter isolates paddle movement from the first Pong example. Add code to keep paddle_y between 0 and 420. The entire paddle must stay inside the window even when an arrow key is held. You can also transfer the tested limit code to the first Pong example.

@exercise exercise1_starter.cpp

### Hint

After updating paddle_y from input, use two if statements to keep it within 0 and 420.

@solution exercise1_solution.cpp

## Try More (Optional)

## Exercise

Move the starter's paddle with the left and right arrow keys. Increase score by 1 only when the ball hits it, and show it with `window.set_title("Score: ", score)`. Moving the paddle aside and missing must not increase the score. Collision detection is provided in the starter.

@exercise game_2_exercise2_starter.cpp

### Hint

Create score with value 0 outside the loop, and increase it inside the collision if.

@solution game_2_exercise2_solution.cpp

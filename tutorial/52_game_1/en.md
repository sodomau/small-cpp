---
title: Combining what you learned into a small game
part: making_things
part-title: Part II — Making Things
goal: Combine what you learned into a small game.
related-example: programs/pong
---

## What you will learn

A **game** receives input, changes its state, and draws that state. This lesson is an assembly activity rather than new syntax.

## Try it

@code example1.cpp

Run the example and move the paddle with the up and down arrow keys. The code reads time and input, updates positions, handles collisions, then draws.

A collision check asks whether objects touch. After crossing a wall, the program corrects the position to the boundary as well as reversing direction. Start by finding the paddle movement instead of changing everything at once.

## Exercise

The starter isolates paddle movement from the first Pong example. Add code to keep paddleY between 0 and 420. The entire paddle must stay inside the window even when an arrow key is held. You can also transfer the tested limit code to the first Pong example.

@exercise exercise1_starter.cpp

### Hint

After updating paddleY from input, use two if statements to keep it within 0 and 420.

@solution exercise1_solution.cpp

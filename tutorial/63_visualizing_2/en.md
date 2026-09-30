---
title: Watching a sort happen
part: algorithms
part-title: Part III — Thinking with Programs
goal: Watch a sorting process.
related-example: programs/bouncing_ball
---

## What you will learn

Drawing **intermediate states**, rather than only the final answer, lets you see an algorithm work.

## Try it

@code example2.cpp

After fixing one position, redraw all bars and wait 0.5 seconds. The position just fixed is red.

Look at the changed array and describe how far sorting has progressed. Read the drawing and sorting sections separately.

## Exercise

Count and print the number of actual swaps in Selection Sort. You may skip swapping a position with itself.

@exercise exercise2_starter.cpp

### Hint

Start `swaps` at 0. Swap and increase it only when smallest != i.

@solution exercise2_solution.cpp

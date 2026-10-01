---
title: Showing numbers as bars
part: algorithms
part-title: Small Steps III — Thinking with Programs
goal: Show numbers as bars.
related-example: programs/bouncing_ball
---

## What you will learn

**Visualization** represents data as pictures. Draw taller bars for larger values to see an array.

## Try it

@code example1.cpp

Multiply each value by 30 for its height. Since y increases downwards, calculate the bar's top as `420 - height`.

Change one array value and check that its bar's height changes.

## Exercise

First practice the position marker for a sorting animation separately. Draw the bar at current in Red and all others in Blue. This exercise is a static picture and does not sort. Change current from 0 through 4 and check that the red bar moves to that position.

@exercise exercise1_starter.cpp

### Hint

In the drawing loop, choose Color by testing `i == current`. In the sorting animation, use the position fixed in that step instead of current.

@solution exercise1_solution.cpp

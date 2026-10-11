---
title: Put Values in Order
part: algorithms
part-title: Small Steps III — Thinking with Programs
goal: Put Values in Order
related-example: reference/array
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Ordering from smallest to largest

### What you will learn

**Sorting** changes an order according to a rule. This method finds the smallest remaining value and fills positions from the front.

### Try it

@code example1.cpp

The outer loop selects the position i to fill; the inner loop finds the minimum's index in the remaining part.

Use temp to hold one value temporarily when swapping. Overwriting it immediately would lose the original. Check that the output is 2, 4, 5, 7, 9.

## Ordering from largest to smallest

### What you will learn

Changing the comparison rule changes the order without changing the procedure. Listing larger values first is **descending order**.

### Try it

@code sorting_2_example2.cpp

Now find the largest remaining value. The comparison changes from < to >, and the output becomes 9, 7, 5, 4, 2.

You do not need to rebuild the whole loop to change sorting direction. Change which value is selected first.

## Showing numbers as bars

### What you will learn

**Visualization** represents data as pictures. Draw taller bars for larger values to see an array.

### Try it

@code visualizing_1_example1.cpp

Multiply each value by 30 for its height. Since y increases downwards, calculate the bar's top as `420 - height`.

Change one array value and check that its bar's height changes.

## Watching a sort happen

### What you will learn

Drawing **intermediate states**, rather than only the final answer, lets you see an algorithm work.

### Try it

@code visualizing_2_example2.cpp

After fixing one position, redraw all bars and wait 0.5 seconds. The position just fixed is red.

Look at the changed array and describe how far sorting has progressed. Read the drawing and sorting sections separately.

## Exercise

Use Selection Sort to arrange `{10, 3, 8, 1, 6}` from smallest to largest.

@exercise exercise1_starter.cpp

### Hint

Apply the lesson's smallest-index pattern.

@solution exercise1_solution.cpp

## Try More (Optional)

## Exercise

Modify Selection Sort to arrange values from largest to smallest.

@exercise sorting_2_exercise2_starter.cpp

### Hint

Find largest instead of smallest, and change the comparison to `>`.

@solution sorting_2_exercise2_solution.cpp

## Exercise

First practice the position marker for a sorting animation separately. Draw the bar at current in Red and all others in Blue. This exercise is a static picture and does not sort. Change current from 0 through 4 and check that the red bar moves to that position.

@exercise visualizing_1_exercise1_starter.cpp

### Hint

In the drawing loop, choose Color by testing `i == current`. In the sorting animation, use the position fixed in that step instead of current.

@solution visualizing_1_exercise1_solution.cpp

## Exercise

Count and print the number of actual swaps in Selection Sort. You may skip swapping a position with itself.

@exercise visualizing_2_exercise2_starter.cpp

### Hint

Start `swaps` at 0. Swap and increase it only when smallest != i.

@solution visualizing_2_exercise2_solution.cpp

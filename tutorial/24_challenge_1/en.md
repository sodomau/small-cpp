---
title: Challenges (Optional)
part: algorithms
part-title: Small Steps III — Thinking with Programs
goal: Challenges (Optional)
related-example: reference/array
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Finding the second-largest value

### What you will learn

Before solving a new problem, define **what counts as the answer and what assumptions hold about the input**. Here we remember two candidates.

### Try it

@code example1.cpp

The example assumes at least two elements and includes duplicates in the ranking. For {9, 9, 3}, the answer is 9. It does not mean the second distinct value.

When a new maximum appears, move the previous maximum into second. For 8, 3, 12, 5, 10, the answer is 10.

## Counting occurrences of the largest value

### What you will learn

Combining two procedures you already know can solve a new problem.

### Try it

@code challenge_2_example2.cpp

First find the maximum, then use a second loop to count elements equal to it. The output is Largest: 9 and How many: 2.

Make each step's responsibility clear before trying to combine the two loops. The array must contain at least one element.

## Exercise

Assume there are at least two distinct values and find the second-smallest value.

@exercise exercise1_starter.cpp

### Hint

Remember smallest and second. When a value is smaller than smallest, update both values together.

@solution exercise1_solution.cpp

## Try More (Optional)

## Exercise

First find the Array's largest value, then count how often it occurs in a second loop.

@exercise challenge_2_exercise2_starter.cpp

### Hint

The first loop finds largest; the second counts occurrences of `numbers[i] == largest`.

@solution challenge_2_exercise2_solution.cpp

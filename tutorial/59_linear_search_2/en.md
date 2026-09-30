---
title: Handling the not-found case
part: algorithms
part-title: Part III — Thinking with Programs
goal: Handle the case when a value is not found.
related-example: reference/array
---

## What you will learn

A search can succeed or fail. The program should distinguish and report both cases.

## Try it

@code example2.cpp

Entering 9 in the console produces Found at 2; entering 8 produces Not found.

Here, break ends only the search loop, and the following if prints the result. Distinguish this from return, which ends the whole function.

## Exercise

Use a linear search to find and print the first position of the character 'a' in a String. Use -1 if absent.

@exercise exercise2_starter.cpp

### Hint

String also supports Length and [], so this is almost the same as searching an Array.

@solution exercise2_solution.cpp

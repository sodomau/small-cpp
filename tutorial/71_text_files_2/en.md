---
title: Reading values back from a file
part: files
part-title: Small Steps IV — Saving and Loading
goal: Read values back from a file.
related-example: reference/file
---

## What you will learn

Opening a saved file retrieves values from a previous run. A **path** identifies the file's location.

## Try it

@code example2.cpp

First create score.txt with the previous lesson. Save this source in the same folder to read the same file.

Open's default mode is reading. Input reads the first line as a string; InputInt reads the second as an integer. Check for Alex's score: 1200. If an error occurs, check the file location and line contents.

## Exercise

Save 950 in `highscore.txt`, reopen it, read it as an int, and print it.

@exercise exercise2_starter.cpp

### Hint

After Write and Close, Open the file again and use `InputInt()`.

@solution exercise2_solution.cpp

---
title: Keeping values after a program ends
part: files
part-title: Small Steps IV — Saving and Loading
goal: Keep values after a program ends.
related-example: reference/file
---

## What you will learn

A **file** holds data that can remain on a storage device after the program ends. A text file records characters you can read in a text editor.

## Try it

@code example1.cpp

Save the source before running. The program writes Alex and 1200 on separate lines in score.txt. FileMode::Write replaces existing contents. Use a practice file you created yourself.

Follow Open → write → Close. A relative-path file usually appears in the saved source's folder. Open it in a text editor and check the two lines.

## Exercise

Save a name on one line and an age on another in `profile.txt`, then close the file.

@exercise exercise1_starter.cpp

### Hint

Open in Write mode and use `file.Print` twice.

@solution exercise1_solution.cpp

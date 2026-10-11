---
title: Read and Write Text Files
part: files
part-title: Small Steps IV — Saving and Loading
goal: Read and Write Text Files
related-example: reference/file
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Keeping values after a program ends

### What you will learn

A **file** holds data that can remain on a storage device after the program ends. A text file records characters you can read in a text editor.

### Try it

@code example1.cpp

Save the source before running. The program writes Alex and 1200 on separate lines in score.txt. FileMode::Write replaces existing contents. Use a practice file you created yourself.

Follow open → write → close. A relative-path file usually appears in the saved source's folder. Open it in a text editor and check the two lines.

## Reading values back from a file

### What you will learn

Opening a saved file retrieves values from a previous run. A **path** identifies the file's location.

### Try it

@code text_files_2_example2.cpp

First create score.txt with the previous lesson. Save this source in the same folder to read the same file.

`open`'s default mode is reading. Input reads the first line as a string; input_int reads the second as an integer. Check for Alex's score: 1200. If an error occurs, check the file location and line contents.

## Exercise

Save a name on one line and an age on another in `profile.txt`, then close the file.

@exercise exercise1_starter.cpp

### Hint

Open in Write mode and use `file.print` twice.

@solution exercise1_solution.cpp

## Try More (Optional)

## Exercise

Save 950 in `highscore.txt`, reopen it, read it as an int, and print it.

@exercise text_files_2_exercise2_starter.cpp

### Hint

After `write` and `close`, `open` the file again and use `input_int()`.

@solution text_files_2_exercise2_solution.cpp

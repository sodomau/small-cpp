---
title: Read and Write Binary Files
part: files
part-title: Small Steps IV — Saving and Loading
goal: Read and Write Binary Files
related-example: reference/file
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Saving numbers in binary form

### What you will learn

A **binary file** records values in a specified byte representation. Distinguish it from a text file, which stores numbers as readable characters.

### Try it

@code example1.cpp

Open in WriteBinary mode and write two integers and one real number in order. save.dat is not a readable sentence for a text editor.

Remember the types and order needed when reading. This mode also replaces existing contents, so use a practice file.

## Reading binary data in its written order

### What you will learn

To restore binary data, read it using **the same types in the same order as when writing**.

### Try it

@code binary_files_2_example2.cpp

Create save.dat with the previous lesson, then run from the same source folder. read_int, read_int, and read_real restore 3, 1250, and 42.5.

Binary is not always better. Data meant for human inspection or long-term exchange needs a separately designed format and compatibility rules.

## Exercise

Save level=5, score=2300, and play_time=18.75 in binary form in `game.dat`.

@exercise exercise1_starter.cpp

### Hint

Use WriteBinary mode, write_int twice, and write_real once.

@solution exercise1_solution.cpp

## Try More (Optional)

## Exercise

Save int 7 and double 3.5 in `state.dat`, reopen it, then read and print both values.

@exercise binary_files_2_exercise2_starter.cpp

### Hint

Close between writing and reading, and use the same types and order when reading.

@solution binary_files_2_exercise2_solution.cpp

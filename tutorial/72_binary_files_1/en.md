---
title: Saving numbers in binary form
part: files
part-title: Small Steps IV — Saving and Loading
goal: Save numbers in binary form.
related-example: reference/file
---

## What you will learn

A **binary file** records values in a specified byte representation. Distinguish it from a text file, which stores numbers as readable characters.

## Try it

@code example1.cpp

Open in WriteBinary mode and write two integers and one real number in order. save.dat is not a readable sentence for a text editor.

Remember the types and order needed when reading. This mode also replaces existing contents, so use a practice file.

## Exercise

Save level=5, score=2300, and playTime=18.75 in binary form in `game.dat`.

@exercise exercise1_starter.cpp

### Hint

Use WriteBinary mode, WriteInt twice, and WriteReal once.

@solution exercise1_solution.cpp

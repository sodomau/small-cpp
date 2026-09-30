---
title: Reading binary data in its written order
part: files
part-title: Part IV — Saving and Loading
goal: Read binary data in its written order.
related-example: reference/file
---

## What you will learn

To restore binary data, read it using **the same types in the same order as when writing**.

## Try it

@code example2.cpp

Create save.dat with the previous lesson, then run from the same source folder. ReadInt, ReadInt, and ReadReal restore 3, 1250, and 42.5.

Binary is not always better. Data meant for human inspection or long-term exchange needs a separately designed format and compatibility rules.

## Exercise

Save int 7 and double 3.5 in `state.dat`, reopen it, then read and print both values.

@exercise exercise2_starter.cpp

### Hint

Close between writing and reading, and use the same types and order when reading.

@solution exercise2_solution.cpp

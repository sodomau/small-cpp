---
title: Binary Files
part: files
part-title: Part IV — Saving and Loading
goal: Store int and double values using their native binary representation and read them back.
related-example: reference/file
---

## Binary Files

Binary I/O stores values as bytes rather than readable digits. Read values back using the same types and order in which they were written. Native binary representation is useful for simple local save data, not portable interchange.

## Examples

@code example1.cpp

Read the code from top to bottom, predict what it will do, then use **Try This Code** and run your copy. Change one small detail and observe the result.

@code example2.cpp

Use `FileMode::AppendBinary` to add new binary values to the end of an existing file. `WriteBinary` truncates existing contents; `AppendBinary` preserves them.

## Exercise 1

Open the starter code and complete it using the ideas from this lesson. Run your program and inspect the result.

@exercise exercise1_starter.cpp

### Hint

Use the examples above as a guide and change one step at a time.

@solution exercise1_solution.cpp

## Exercise 2

Open the starter code and complete it using the ideas from this lesson. Run your program and inspect the result.

@exercise exercise2_starter.cpp

### Hint

Use the examples above as a guide and change one step at a time.

@solution exercise2_solution.cpp

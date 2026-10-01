---
title: Displaying a timer's value
part: making_things
part-title: Small Steps II — Making Things
goal: Display a timer's value on the screen.
related-example: reference/timer
---

## What you will learn

A callback can change a value while the window loop reads that value and draws it.

## Try it

@code example2.cpp

OnSecond increases the global seconds, and DrawText displays its current value. **Format** returns a String joining text and values. Unlike Print, it does not produce output itself.

Timer is not a separate computation thread. Callbacks run when Show or Sleep processes events, so a long calculation may delay them. Use StopWatch for accurate elapsed-time measurement.

## Exercise

Have a Timer callback increase level by 1 each second. In the Window loop, show the current level in the title with `SetTitle("Level ", level)`.

@exercise exercise2_starter.cpp

### Hint

Change only the global int level in the callback and update the Window title in the main loop.

@solution exercise2_solution.cpp

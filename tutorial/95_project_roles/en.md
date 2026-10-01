---
title: Give Each File a Job
part: projects
part-title: Small Steps VIII — Build with Several Files
goal: Pass values to a function and receive its result.
related-example: reference/console
---

## Separate the score calculation

Name files after their jobs. Create a new `ScoreCard` project. Keep `main.cpp`, `score.h`, and `score.cpp` in the same folder and replace their contents as follows.

### score.h
```cpp
#pragma once

int AddPoints(int score, int points);
```

### score.cpp
```cpp
#include "score.h"

int AddPoints(int score, int points)
{
    return score + points;
}
```

### main.cpp
```cpp
#include "score.h"

void SmallMain()
{
    int score = 0;
    score = AddPoints(score, 10);
    score = AddPoints(score, 20);
    Print(score);
}
```

**Run Project** prints `30`. `main.cpp` controls the program's flow; `score.cpp` handles the calculation. The score is a local variable in main. Passing values in and returning a new value avoids a shared global variable.

Start with **a header named after its source file**. Put function declarations in the header and definitions in the source. You do not need a separate file for every small function.

## Check the behavior in one file

![main.cpp controls the flow while score.cpp handles the calculation.](project.png)

@code example.cpp

## Exercise — Check it yourself

Add another call worth 5 points to print 35 in the one-file practice. Then add the same call to main.cpp in your project. Do score.h and score.cpp need to change?

@exercise exercise_starter.cpp

### Hint

Use the menus described above. The solution below is for the one-file practice. Apply the same change to the file with that job in your project.

@solution exercise_solution.cpp

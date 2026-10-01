---
title: Set a File Aside
part: projects
part-title: Small Steps VIII — Build with Several Files
goal: Exclude a file from the build without deleting it.
related-example: reference/console
---

## One starting point

All included `.cpp` files become one program. An old practice file with another `SmallMain` introduces a second starting point.

In your Greeting project, use **New Source File…** to create `practice.cpp` and put the following code in it.

@code example.cpp

Run Project reports multiple starting functions. Right-click `practice.cpp` and choose **Exclude from Project**. It turns gray and italic with `(Excluded)` beside it. You can now run the Greeting program.

## Excluding is different from deleting

The excluded file stays on disk and can still be opened. Its tab shows **[Excluded]** too. **Include in Project** restores its usual appearance. Restoring it also restores the conflicting starting point.

The IDE saves exclusions in `small.project`. You do not need to write that file yourself. Exclusions remain when you reopen the project.

Use a separate project for a different program. Excluding a file that defines a needed function can cause a linker error because the function cannot be found.

## Exercise — Check it yourself

Change the practice file's message and save. Exclude it, close the project, and reopen it. Check that both the file and its exclusion remain.

@exercise exercise_starter.cpp

### Hint

Use the menus described above. The solution below is for the one-file practice. Apply the same change to the file with that job in your project.

@solution exercise_solution.cpp

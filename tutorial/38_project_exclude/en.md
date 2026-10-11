---
title: Manage and Share a Project
part: projects
part-title: Small Steps VIII — Build with Several Files
goal: Manage and Share a Project
related-example: reference/console
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Set a File Aside

### One starting point

All included `.cpp` files become one program. An old practice file with another `small_main` introduces a second starting point.

In your Greeting project, use **New Source File…** to create `practice.cpp` and put the following code in it.

@code example.cpp

Run Project reports multiple starting functions. Right-click `practice.cpp` and choose **Exclude from Project**. It turns gray and italic with `(Excluded)` beside it. You can now run the Greeting program.

### Excluding is different from deleting

The excluded file stays on disk and can still be opened. Its tab shows **[Excluded]** too. **Include in Project** restores its usual appearance. Restoring it also restores the conflicting starting point.

The IDE saves exclusions in `small.project`. You do not need to write that file yourself. Exclusions remain when you reopen the project.

Use a separate project for a different program. Excluding a file that defines a needed function can cause a linker error because the function cannot be found.

## Share a Project or Its Program

### Will your friend run it or help edit it?

What you send depends on the goal. Try both with the ScoreCard project you made earlier.

This is the one-file practice version of the score program. Keep using the three files from the earlier lesson in your actual project.

@code project_share_example.cpp

### Send a runnable program

Add `input();` after `print(score);` in `main.cpp` and save before publishing, so the console stays open.

Choose **File → Publish Project…** and a new export folder. All included source files are compiled into one exe. Selecting the score.h tab does not change the program you publish.

Run the exported exe and check that it prints `30`. Send a ZIP of the entire export folder, including the DLLs, plugins, and licenses. Your friend extracts it on Windows x64 and runs the exe without installing Small C++. Small Steps VII explains the details.

Publish does not automatically include the original `.cpp`, `.h`, or `small.project`. You can include selected images, sounds, and other files needed at runtime.

### Send a project to edit together

Save and ZIP the **original project folder** when you want help editing the code. Right-click the project name and choose **Show Project in File Explorer** to find that folder. Include the `.cpp`, `.h`, required resources, and `small.project` if it exists. Your friend extracts it and uses **Open Project (Folder)… → Open This Folder** in Small C++. Avoid absolute paths tied to your own computer in the program.

The folder name is the project name. A copy with a different folder name works too.

### Find out more — subfolders

Sources in subfolders are included automatically. Right-click a blank area in the file list and choose **New Folder…** to make a folder. Empty folders are visible and a new folder is selected immediately. Right-click a folder and choose **New Source File…** or **New Header File…** to create a file there. Right-click a file to create beside it. A blank area or the main New button creates files in the project root. New Folder also creates inside a clicked folder or beside a clicked file. One folder is enough to start.

## Exercise — Check it yourself

Change the practice file's message and save. Exclude it, close the project, and reopen it. Check that both the file and its exclusion remain.

@exercise exercise_starter.cpp

### Hint

Use the menus described above. The solution below is for the one-file practice. Apply the same change to the file with that job in your project.

@solution exercise_solution.cpp

## Try More (Optional)

## Exercise — Check it yourself

Add 5 points in the one-file practice and in your project's main.cpp to print 35. Publish and test the updated program. Also ZIP the original project, extract it elsewhere, and reopen that copy.

@exercise project_share_exercise_starter.cpp

### Hint

Use the menus described above. The solution below is for the one-file practice. Apply the same change to the file with that job in your project.

@solution project_share_exercise_solution.cpp

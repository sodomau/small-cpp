---
title: Share a Project or Its Program
part: projects
part-title: Small Steps VIII — Build with Several Files
goal: Distinguish an editable project from a runnable package.
related-example: reference/console
---

## Will your friend run it or help edit it?

What you send depends on the goal. Try both with the ScoreCard project you made earlier.

This is the one-file practice version of the score program. Keep using the three files from the earlier lesson in your actual project.

@code example.cpp

## Send a runnable program

Add `input();` after `print(score);` in `main.cpp` and save before publishing, so the console stays open.

Choose **File → Publish Project…** and a new export folder. All included source files are compiled into one exe. Selecting the score.h tab does not change the program you publish.

Run the exported exe and check that it prints `30`. Send a ZIP of the entire export folder, including the DLLs, plugins, and licenses. Your friend extracts it on Windows x64 and runs the exe without installing Small C++. Small Steps VII explains the details.

Publish does not automatically include the original `.cpp`, `.h`, or `small.project`. You can include selected images, sounds, and other files needed at runtime.

## Send a project to edit together

Save and ZIP the **original project folder** when you want help editing the code. Right-click the project name and choose **Show Project in File Explorer** to find that folder. Include the `.cpp`, `.h`, required resources, and `small.project` if it exists. Your friend extracts it and uses **Open Project (Folder)… → Open This Folder** in Small C++. Avoid absolute paths tied to your own computer in the program.

The folder name is the project name. A copy with a different folder name works too.

## Find out more — subfolders

Sources in subfolders are included automatically. Right-click a blank area in the file list and choose **New Folder…** to make a folder. Empty folders are visible and a new folder is selected immediately. Right-click a folder and choose **New Source File…** or **New Header File…** to create a file there. Right-click a file to create beside it. A blank area or the main New button creates files in the project root. New Folder also creates inside a clicked folder or beside a clicked file. One folder is enough to start.

## Exercise — Check it yourself

Add 5 points in the one-file practice and in your project's main.cpp to print 35. Publish and test the updated program. Also ZIP the original project, extract it elsewhere, and reopen that copy.

@exercise exercise_starter.cpp

### Hint

Use the menus described above. The solution below is for the one-file practice. Apply the same change to the file with that job in your project.

@solution exercise_solution.cpp

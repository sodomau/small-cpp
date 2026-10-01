---
title: A Folder Is a Project
part: projects
part-title: Small Steps VIII — Build with Several Files
goal: Create a project and run the whole program.
related-example: reference/console
---

## When your code gets longer

Keep using one file while it is enough. Use a project when you want to separate functions by their jobs. **One folder is one project.**

## Make your first project

1. Choose **File → New Project…**.
2. Choose where to put it and enter `Greeting` as its name.
3. Replace the generated `main.cpp` with the code below and save it.

@code example.cpp

Choose **Run Project**. You will see `Hello, project!`. The name below PROJECT is the folder name. The window title and status bar also identify your project.

For an existing folder, choose **File → Open Project (Folder)…**, enter that folder, then choose **Open This Folder**. You do not need a `small.project` file.

## A tab and a project are different

A tab is the file you are reading or editing. Run Project uses all included `.cpp` files together, regardless of the selected tab. Closing a tab keeps its file in the project. A file from another folder has **[Outside Project]** on its tab and is not used when running the project.

**File → Close Project** closes the project without deleting its files.

## Find the actual folder

Right-click the project name or a blank area in its file list and choose **Show Project in File Explorer**. This opens the project folder. Right-click a file or its tab and choose **Show in File Explorer** to see that file selected. This action is unavailable for files you have not saved yet.

## Exercise — Check it yourself

Change the message and save. Close the project, reopen the same folder, and run it.

@exercise exercise_starter.cpp

### Hint

Use the menus described above. The solution below is for the one-file practice. Apply the same change to the file with that job in your project.

@solution exercise_solution.cpp

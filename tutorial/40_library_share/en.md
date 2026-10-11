---
title: Share a Program That Uses Libraries
part: libraries
part-title: Small Steps IX — Use External Libraries
goal: Share a Program That Uses Libraries
related-example: reference/console
---

Explore one topic in small steps. Try the examples one at a time and take a break whenever you need. Choose how many extra exercises you want to try.

## Share a Program That Uses Libraries

### Is the executable enough?

Practice Publish with the basic greeting first. Add `input();` at the end if you want its console to stay open.

@code example.cpp

Also try **File → Publish Program…** with the earlier fmt example. In a project, use Publish Project…. Publish checks ordinary DLL dependencies and includes them. ZIP the **entire exported folder**, and test on a computer without the Small development environment.

Publish cannot discover everything. Plugins loaded dynamically, images, sounds, and data may need to be added manually. Libraries have different redistribution terms, so check their licenses too. Available notices and package information in the exported licenses folder help with that review. Publish is also a Small IDE feature, not a C++ standard feature.

### Find out more — MSYS2 and the terminal

The Windows Small C++ distribution includes an **MSYS2 development environment**. The IDE builds your code using its compiler and installs packages using **pacman**. **pkg-config** finds the compilation and linking options required by a library. These tools are not part of the C++ standard.

**Tools → MSYS2 Terminal** opens a window where you enter commands to run tools. Later, you can use it to inspect, install, or remove packages, or run the compiler directly. You do not need to use it now. When you become curious about what happens behind the IDE, explore the [official MSYS2 documentation](https://www.msys2.org/docs/what-is-msys2/) and package management. Updating the entire environment is different from installing one package; read the official update procedure first.

## Exercise — Before sending it to a friend

Change the greeting to friend, add `input();`, and Publish. Run the exported exe to check the output and that the console stays open. Then ZIP the entire folder. Try the same process with the fmt version.

@exercise exercise_starter.cpp

### Hint

The original project folder and the runnable export folder are different.

@solution exercise_solution.cpp

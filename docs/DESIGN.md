# Small C++ Design

## Vision

C++ can be easy to use when beginners are not forced to confront all
historical, low-level, and highly flexible features at once. Small C++
presents **simple C++**, not a toy language.

## Principles

1.  **Hide accidental complexity, not fundamental concepts.**
2.  **Complex implementation, simple use.** GDB/MI complexity is
    internal; learners see familiar debugging actions.
3.  **Prefer explicit structure over hidden magic.** Runtime lifetime is
    `InitializeSmall → learner code → ShutdownSmall`; exit-time cleanup
    was removed after Qt/audio ordering problems.
4.  **Keep the core small.** Domain-specific educational capabilities
    belong in extensions when practical.
5.  **Convention where it removes duplication; manifests where they
    clarify packages.** Tutorial order comes from `NN_id`; extensions
    retain `extension.json`.
6.  **Use standards when they fit.** Tutorials use Markdown and standard
    Markdown images; custom tags are only `@code`, `@exercise`,
    `@solution`.

## IDE philosophy

Support the learner loop:

``` text
read → edit → run → observe → diagnose → debug → change
```

Do not grow into a miniature professional IDE without an educational
reason. Debugger semantics remain conventional; Small/STL implementation
frames are normally filtered from learner stepping.

## Learning path

`SmallMain()` → basic C++ → visual/interactive programs →
algorithms/files → types/references → standard library → real `main()` →
ordinary C++.

## Current scope

Single-file mode includes editing, compile/run,
graphics/input/timing/sound/files, Image extension, Examples/API
Reference, GDB/MI debugging, portable distribution, and multilingual
external tutorials. It is feature-complete for now; further changes
should be maintenance/usability driven.

The current core content pack supplies 88 Korean Small Steps lessons.
Multilingual loading remains supported, but available translations depend
on the installed content. The full 40-point manifesto in `PHILOSOPHY.md`
remains the detailed design reference.

## Future direction

### Near term: beginner usability testing

Observe hesitation, unclear diagnostics, tutorial mismatches, API
discoverability, and debugger comprehension. Prefer observed learner
friction over feature accumulation.

### Next major milestone: Project Mode

Introduce only what is needed to grow from one file to ordinary C++
projects: - multiple source files; - header files; - simple project
structure; - whole-project build; - debugging across user files; -
extensions across project files.

The exact project representation is intentionally open until prototyped
and tested. Small C++ is not intended to replace Visual Studio, Qt
Creator, or VS Code.

### Tutorial ecosystem

Possible additions: more languages, course-specific packs, extension
lessons, richer diagrams, independently distributed content.

### Educational extensions

Possible future domains include robotics, sensors, and physical
computing. These are possibilities, not commitments.

### IDE localization

Tutorial languages are already separate. Full IDE UI localization should
later be implemented systematically as its own feature.

### Platforms

Portable Windows is the tested path. Other platforms can be considered
later without compromising learner simplicity.

## Non-goals

Avoid professional IDE features without educational justification,
premature build-system complexity, an overly generic extension
ecosystem, duplicated content that can drift, and altered programming
semantics merely to avoid explanation.

## Open Project Mode questions

What is the smallest useful project model? Manifest or convention? How
should header/source pairs be introduced? How should multi-file errors
and Step Into filtering work? Which concepts belong in Small versus
standard tooling?

## Runtime lifetime

Small runtime resources have explicit lifetime:

``` text
InitializeSmall → program → ShutdownSmall
```

Qt/audio cleanup is not delegated to exit-time static destruction. The
console pause used by IDE Run/Debug is a separate IDE-only linked
object, not runtime policy.

## Origin

Small C++ was created by Sunghyun Cho, who was introduced to the world of programming through **GW-BASIC** as a child. GW-BASIC made programming feel immediate: write a few lines, run them, and see something happen.

The name **Small C++** is also a nod to **Small Basic**. While Small C++ is not based on Small Basic, the name reflects a shared aspiration: making the first experience of programming small, approachable, and rewarding.

Small C++ grew from a desire to bring some of the immediacy and accessibility of that early BASIC experience to modern C++ education—without creating a new language. It is real C++, with a smaller and friendlier starting point and a natural path toward the full language.

**The immediacy of BASIC. The path to C++.**

## Project

Small C++ was designed and developed by **Sunghyun Cho, POSTECH**.

Contact: `s.cho@postech.ac.kr`

# Development History

## Single-file foundation

Small C++ began as a compact educational C++ environment: simple
learner-facing APIs, `SmallMain()`, examples, Learn UI, and a portable
runtime.

## API/tutorial refinement

The API was kept deliberately small and readable. Tutorial content grew
to a 36-lesson path from first programs through standard C++ graduation.

## Extension architecture

The core was kept small and Image became the first real extension, with
an explicit `extension.json` manifest.

## Debugger

A standalone GDB/MI feasibility probe was developed before integration.
Work included MI prompt framing, asynchronous `*stopped` handling,
user-global filtering, readable Small String values, and user-code-only
Step Into. The IDE then gained breakpoints, live breakpoint changes,
Continue/Over/Into/Out, Variables, a learner console, and clean exit
handling.

## Portability

Testing on another machine exposed hidden dependencies on the developer
Qt installation. Packaging was changed to include learner linker
libraries and a `SmallDeployProbe` so `windeployqt` discovers
runtime/plugin dependencies used by learner programs, including
Multimedia.

A useful regression technique was to temporarily hide `C:\Qt` on the
development machine.

## Explicit runtime lifetime

Sound worked correctly but crashed during process shutdown. GDB isolated
the crash to shutdown ordering. Exit-time cleanup was replaced with
explicit `InitializeSmall()` / `ShutdownSmall()` lifetime management.
This also made the architecture clearer.

## External tutorials

Tutorials moved from JSON + fragmented Markdown + C++ embedded in Qt
resources to external Markdown + shared C++ bundles. Lesson order/id
comes from `NN_id`; only `@code`, `@exercise`, and `@solution` are
custom tags. Standard Markdown images are supported.

## Multilingual tutorials

Language-specific files such as `ko.md` and `en.md` share C++ and image
assets. `languages.json` drives Tutorial Language settings. Core 36
lessons and Image extension lessons have Korean and English content.

## v0.76b milestone

v0.76b established the single-file baseline. Single-file mode was
considered complete enough to enter maintenance/usability testing. The
next major development direction is Project Mode.

## Current repository baseline

The repository imports v0.76f, including the separate IDE-only pause support
archive and generated `IdePauseFile` configuration. The latest core tutorial
is the user's Korean 88-lesson Small Steps pack; earlier Korean/English content
is preserved in Git history. Project Mode remains a proposed next direction.

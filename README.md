Development: [workflow and build instructions](docs/DEVELOPMENT.md) · [setup validation](docs/SETUP_VALIDATION.md) · [design philosophy](docs/PHILOSOPHY.md)

Current core tutorial: **88 Korean Small Steps lessons**, imported from
`SmallCpp-Core-Tutorial-KO-Small-Steps.zip`. See the [contents](docs/tutorial-small-steps/CONTENTS.md),
[teacher notes](docs/tutorial-small-steps/TEACHER.md), and [integration notes](docs/TUTORIAL_SMALL_STEPS.md).

# Small C++ IDE v0.76f — IdePauseFile Build Fix

Fixes the generated `SmallBuildConfig.h`: it now explicitly contains
`SmallBuildConfig::IdePauseFile`.

The complete IDE-only pause wiring is present:
- `small_ide_pause` static library target;
- copied into the runtime SDK;
- `small_sdk` depends on it;
- generated config exposes its filename;
- Run and Debug both link it;
- Small runtime itself does not register the pause.

After opening this version, let Qt Creator reconfigure CMake so the generated
SmallBuildConfig.h is regenerated before building.

# Small C++ IDE v0.76e — IDE-only Console Pause

Console pause policy is now separated from the Small runtime.

- `InitializeSmall()` no longer registers an atexit pause.
- New `small_ide_pause` support archive contains the exit-pause registration.
- Small IDE Run links `small_ide_pause` for both SmallMain and user-written main.
- Small IDE Debug does the same.
- The public Small API/runtime is unaware of IDE pause policy.
- A future Project/Release build can get normal immediate process termination
  simply by omitting `small_ide_pause` from the link.

The v0.76d Learn-window geometry/minimize/maximize polish and all v0.76c
FileMode/tutorial fixes are retained.

# Small C++ IDE v0.76d — Learn Window Polish

Baseline includes the v0.76c FileMode/main-tutorial fixes plus the Hidden Main
Pause Patch.

Tutorial, Examples, and API Reference are now ordinary resizable top-level
windows with Minimize, Maximize/Restore, and Close controls. Each window stores
its geometry in QSettings and restores its previous size/position the next time
it is created. Existing modeless behavior is unchanged.

# Small C++ IDE v0.76c — File and main() Tutorial Fix

- Adds `FileMode::AppendBinary`.
- `WriteInt` and `WriteReal` accept both `WriteBinary` and `AppendBinary`.
- Binary-file tutorial documents append mode.
- The SmallMain-to-main lesson now explicitly teaches the full runtime lifecycle:
  `InitializeSmall()` → program → `ShutdownSmall()` → return.
- Both main() exercise starters explicitly mention shutdown.

# Small C++ IDE v0.76b — Complete English Tutorials

Adds English `en.md` content for all 36 core lessons and all 3 Image-extension
lessons. English and Korean share the same runnable C++ examples, starter code,
solutions, and image assets. No loader or UI behavior changes are required.

# Small C++ IDE v0.76a — Tutorial Preview Polish

Tutorial UI chrome is English-only for now. Full IDE localization is deferred.

Tutorial code previews now use a line-number-only gutter. Breakpoint dots,
debug-line markers, and breakpoint clicking are disabled, and the compact
line-number gutter has dedicated padding so numbers are not clipped. Normal
editor/debugger gutter behavior is unchanged.

# Small C++ IDE v0.76 — Tutorial Languages

Adds Settings > Tutorial Language, populated by `tutorial/languages.json`.
Language selection is persisted with QSettings and applies to both core and
extension tutorials.

Lessons now use language-code Markdown files (`ko.md`, `en.md`, etc.) beside
shared C++ and image assets. If the selected translation is absent, the loader
falls back to the configured default language, allowing translations to be
added incrementally after build.

Lesson 01 includes an English translation as a working example. Other lessons
currently fall back to Korean until their `en.md` files are added.

# Small C++ IDE v0.75a — Tutorial Image Compile Fix

Fixes all TutorialBrowser `prose()` call sites after the image-support API
changed from `(markdown, parent)` to `(markdown, baseDirectory, parent)`.

- Lesson prose, exercise prompts, and hints use `lesson.sourceDirectory`.
- IDE-owned status/help text uses an empty base directory.
- Standard relative Markdown image support from v0.75 is unchanged.

# Small C++ IDE v0.75 — Tutorial Images

Tutorial Markdown now supports standard relative Markdown images.

Example lesson layout:

    11_drawing/
        lesson.md
        images/
            coordinates.png
        example1.cpp

Inside lesson.md:

    ![Window coordinate system](images/coordinates.png)

No Small-specific image tag is used. TutorialBrowser gives QTextDocument the
lesson directory as its base URL, so standard relative Markdown paths resolve
for both core and extension tutorials. The same base directory is used for
lesson prose, goals, exercise prompts, and hints.

Images remain ordinary external tutorial content and are automatically copied
by the existing tutorial/extension packaging.

# Small C++ IDE v0.74 — Convention-based Tutorial Ordering

Tutorial JSON catalogs are gone. Tutorial order and IDs are derived from
lesson directory names:

    01_hello/
    02_variables/
    ...

For a core lesson:
- folder `NN_id` gives order + id;
- `lesson.md` front matter contains title, part, part-title, goal, and optional
  related-example;
- lesson content is Markdown with @code, @exercise, @solution tags.

Extensions retain `extension.json` because it is a useful explicit package
manifest. Its `tutorial` field points only to the tutorial root. If that
directory exists, lessons are discovered exactly like core lessons:

    extensions/image/tutorial/
        01_create/
        02_pixels/
        03_files/

Within each extension, NN_ defines lesson order. Extensions themselves have no
curriculum order; the IDE currently uses name sorting only for stable display.

No tutorial catalog.json or per-lesson lesson.json is required.

# Small C++ IDE v0.73 — Tutorial Content Refresh

Tutorials are now external content bundles rather than compiled Qt resources.

Each lesson is a folder containing:
- `lesson.md` — metadata, prose, ordering, and special tags;
- `.cpp` files referenced by the lesson.

Supported special tags:
- `@code file.cpp`
- `@exercise file.cpp`
- `@solution file.cpp`

The old per-lesson JSON and fragmented Markdown files are removed. The core
`catalog.json` and `SmallTutorials.qrc` are also removed.

`lesson.md` uses a small front-matter block for id/title/part/number/goal.
Everything else is ordinary Markdown in reading order. Existing 36 lessons
were migrated automatically without changing their C++ source files.

TutorialCatalog loads `tutorial/` beside SmallCppIDE.exe at runtime. Therefore
tutorial text, code, or whole lesson folders can be changed/added after the IDE
has been built. Release packaging copies the tutorial folder as content.

# Small C++ IDE v0.72

Small C++ is a compact educational C++ environment that keeps beginner-facing
syntax and APIs small while remaining ordinary C++ underneath.

## Current runtime lifecycle

SmallMain programs use an explicit hidden entry point:

    Small::InitializeSmall(argc, argv);
    SmallMain();
    Small::ShutdownSmall();

There is no atexit-based Qt cleanup. Advanced programs that write their own
`main()` call InitializeSmall and ShutdownSmall explicitly.

ShutdownSmall tears down Small audio resources while QApplication is alive,
then destroys QApplication, then performs the normal console pause.

## Debugger

The built-in GDB/MI debugger supports breakpoints (including live changes),
Continue, Step Over/Into/Out, user locals/globals, learner-facing String
display, a separate learner console, and clean session termination. Runtime
signals are reported concisely; raw developer backtraces are not shown in the
learner UI.

## Portable packaging

Release packaging includes:
- the MinGW compiler/debugger toolchain;
- Small runtime and extensions;
- Qt import libraries needed to link learner programs;
- Qt runtime DLLs/plugins discovered using the packaging-only
  SmallDeployProbe plus windeployqt.

SmallDeployProbe is removed from the final package.

## Packaging

1. Build the Release configuration in Qt Creator.
2. Run `package_release.bat`.
3. Distribute the generated `SmallCpp-Portable` folder.

A clean portability test is to close Qt Creator, temporarily hide the local
Qt installation, and test Print, Window, Sound, Image, and Debug from the
portable package.

## Next planned work

Tutorial content format/loader simplification. The current tutorial content is
still the existing JSON + Markdown + C++ structure.

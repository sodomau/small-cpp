# Regression validation — 2026-09-30

The tutorial maintenance Windows Debug build and CTest suite passed **29/29 checks**, with zero
failures. Environment: Qt 6.11.2, MinGW GCC 13.1.0, Ninja, C++20; Qt UI tests use
the offscreen platform. Commands are documented in `DEVELOPMENT.md`.

## Updated expectations

- External core lesson folders replace obsolete JSON catalogs and Qt resources:
  88 core lessons, 264 C++ files, and Korean fallback for unavailable translations.
- Learn tests locate independent top-level browser windows, release them between
  cases, and check 91 total lessons, 94 exercises, and 24 examples including Image.
- Validators use current lesson paths, metadata, API names, and UTF-8 explicitly;
  the obsolete debugger version assertion is removed while integration checks remain.
- The manual-main fixture uses the actual namespaced initialization/print/shutdown API.
- All 20 Python validators run through CTest. Six validator regression cases check
  translation fallback and rejection of missing sources, orphan solutions, unsafe
  paths, unknown related examples, and duplicate lesson numbers.

## Small implementation fixes found by tests

Settings construction now honors the configured QSettings backend. Normal runs
retain native settings under the same organization/application names; tests use
isolated temporary INI files instead of the Windows registry.

Appearance changes preserve a document's existing modified state. Tests check
both clean read-only previews and edited copies across theme changes.
Runtime APIs, lesson content, source layout, and product architecture are preserved.

## Additional tutorial validation

All **264 core programs compiled and linked** against the actual Small runtime.
Six representative console fixtures also passed exact exit-code, stdout, and
stderr checks. These fixtures replace obsolete lesson-output fixtures; they are
representative coverage, not execution of every lesson. The local machine-readable
report is `build/local-debug/tutorial-validation.json`.

Qt test logs are retained under the ignored build directory. This validation
covers automated offscreen UI behavior and does not establish interactive sound,
mouse/keyboard behavior, a live GDB session, or release-package operation.
The earlier failures remain documented as history in `SETUP_VALIDATION.md`.

## Console pause follow-up

After this fix, all **30 checks pass**: the existing 29 passed in the full run,
and the new pause check passed after correcting transient Windows executable
cleanup handling in its test harness.

Manual use exposed an original v0.76f linking defect that the prior suite did
not cover. `small_ide_pause` contains only a static initializer; linking its
archive normally does not extract that object. Run and Debug now force extraction
of this archive alone. The runtime remains independent of IDE pause policy.
The actual IDE pause callback also honors the existing test-only bypass.

`small_ide_console_pause` compiles against the actual pause archive and keeps
stdin open to verify that normal execution waits until Enter is supplied. It also
checks that standalone programs without the archive and test-mode programs exit
immediately. This is a process/input test, not a visual Windows console test.

## First public package: String debugger follow-up (2026-09-30)

Portable-package QA exposed a pre-existing defect: GDB reports the class as
`Small::String`, while the controller recognized only `String`. Its attempted
inline `c_str()` call was also unsuitable when that function was not emitted.
The controller now recognizes both spellings and reads the bundled GCC
libstdc++ string buffer without executing a function in the paused program.
Failed String reads report an unavailable value and continue refreshing variables.

A live GDB regression pauses after initializing String variables and checks
text, an empty string and embedded quotes, then resumes to a clean exit.
The full Release CTest suite passed **30/30** after the main fix; the final
quote/error-handling refinement was verified with the live String regression.
The current buffer expression targets the supported GCC/libstdc++ kit; it
must be revisited for a different standard-library implementation.

## v0.76i source reconciliation (2026-09-30)

The later origin-story archive uses CMake version 0.76.9. Its changes were
compared with the original import before applying them to the current tree.
The IDE pause is now a directly linked object for both Run and Debug, replacing
the earlier whole-archive workaround. The process/input regression now links
that real object and verifies normal Enter waiting, standalone exit and the
existing test bypass. The About regression checks the restored origin and
developer text while retaining the current license summary.

Public API, design and guide documents and the distribution README were restored.
The current Getting Started guide retains QSS, debugger and Korean tutorial
information. Packaging explicitly includes the four public guides. The current
ignore rules, license preparation, themes and debugger fixes remain in place.

Validation: Release build succeeded; full CTest passed 30/30 (228.95 s).
The identifier validator spent 152.56 s scanning generated third-party headers;
its scope was then limited to project source directories. Checks 18–30 were
rerun and passed 13/13, with the identifier check taking 0.27 s.
The local portable folder includes all four guides, its README, and the new
pause object. Print, user-written main, Window, Sound and Image each compiled,
linked with that object and ran successfully using package/Windows paths only.
A separate clean PC test remains pending. No published release was replaced.

## Complete English tutorial edition (2026-09-30)

Added explicit English files for all 88 Small Steps core lessons and expanded
the three existing Image English lessons to include the original explanations,
exercise tasks and hints. Korean Markdown and all runnable C++ files remain
unchanged. The language manifest offers English while keeping Korean as default.
The English index links to every lesson and is included by portable packaging.

The new content validator requires real English coverage without fallback, no
remaining Hangul, identical code/exercise/solution directives and unchanged
example/output fences. Qt regressions load translated titles and shared answers,
check unknown-language fallback, select English in Settings, display its first
lesson and verify preference persistence and the shared code preview.

Release build succeeded. Full CTest passed **31/31** in 74.08 seconds. The local
portable review folder was updated with both language editions; published release
assets have not been changed by this tutorial work.

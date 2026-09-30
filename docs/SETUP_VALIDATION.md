# Repository setup validation — 2026-09-30

## Source integrity

Imported archive: `SmallCpp-IDE-v0.76f-ide-pause-config-fix.zip`.
SHA-256: `067A6773DCAC94B50EB6B185EB05318E40DE300A55FAB79F697D262BB59DA637`.

Compared all 499 archive files by SHA-256 after setup. The only changed archive
files are `.gitignore` and `tests/test_qt.cpp`. Product source, learner content,
images and design documents remain byte-for-byte unchanged. Added files contain
development instructions and these validation results. Historical whitespace
warnings from the import were preserved rather than rewriting source documents.

## Build and tests

Windows 11, Qt 6.11.2 MinGW 64-bit, GCC 13.1.0, Ninja, C++20.
Configured `ide/` with `SMALL_BUILD_TESTS=ON` into `build/local-debug`.
After the test-only compatibility fix, all default build targets compile and link.

Initial test-enabled compilation exposed a missing `EntryPoint.h` include and
obsolete one-argument `ExtensionRegistry::detect` calls. Both are fixed only in
the test source; product APIs are unchanged.

Qt dependencies were deployed locally under the ignored build directory.
CTest result: **6 passed, 4 failed, out of 10**.

Passed: `small_values`, `small_manual_main`, `small_manual_main_default`,
`small_standard_main`, `small_tabs`, `small_example_catalog`.

Remaining failures:

- `small_qt`: a direct run with file logging reports 16 passing cases and one
  failing case, `buildControllerRunsManualMain`. Its generated learner program
  uses unqualified `InitializeSmall` and `Print`, which are not declared in that
  manual-main context. This is recorded for follow-up, without changing product policy.
- `small_examples_ui`: segmentation fault in this offscreen Windows test run.
- `small_tutorial_ui`: segmentation fault in this offscreen Windows test run.
- `small_tutorial_content`: obsolete verifier expects removed `tutorial/catalog.json`.

Targeted tests for the changed test code pass: `detectsExtensionsFromIncludes`
and `detectsRealMainOnly` (four passes including setup/cleanup, zero failures).

Ran all 20 `tools/verify_*.py` scripts with Python UTF-8 mode: **15 passed, 5 failed**.
The remaining historical checks are:

- `verify_comments_content.py`: expects removed `tutorial/01_hello/after.md`.
- `verify_debugger.py`: asserts old CMake `VERSION 0.66`.
- `verify_extensions.py`: expects removed extension tutorial `catalog.json`.
- `verify_tutorial.py`: expects removed core tutorial `catalog.json`.
- `verify_ui_packaging.py`: expects removed `ide/SmallTutorials.qrc`.

The current test suite is not fully green. Do not suppress or relabel these failures.
GUI interaction and optional tutorial/example compilation targets were not validated
as part of this repository setup. Logs remain in the local ignored build directory.

## Git review

Verified that build output, local Qt Creator settings, CMake user presets, editor
settings and private-key files are ignored. Learner images, resources and historical
reports remain tracked. The post-import test-only diff passes `git diff --check`.
The source archive has no existing Git history; its version ZIPs were not turned
into fabricated historical commits.

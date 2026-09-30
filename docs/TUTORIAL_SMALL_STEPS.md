# Korean Small Steps tutorial integration — 2026-09-30

The user identified `SmallCpp-Core-Tutorial-KO-Small-Steps.zip` as the latest
core tutorial. It replaces the previous core tutorial as a complete folder set:
**88 Korean lessons**, rather than merging differently numbered lesson folders.

Archive SHA-256:
`B8A265AD06F842FB30201AC92955A5123FA8A3C9D4EBD066A304C8B5894E7503`.

## Content and preservation

- `tutorial/` contains the archive's complete active tutorial and language manifest.
- `docs/tutorial-small-steps/` contains the archive's README, contents, reading
  material, teacher notes, reference material, and original `validation.json`.
  Paths such as `tutorial/` in those original documents refer to the repository
  root, not this relocated documentation directory.
- All 359 archive files were compared byte-for-byte with their imported copies.
- Diff review found Markdown hard-break spaces and extra final blank lines in
  the source archive. They are retained to preserve the supplied content;
  `git diff --check` reports these known whitespace warnings.
- The earlier tutorial remains recoverable from commit `02326b5` and a local
  backup outside the repository. The ZIPs in OneDrive are unchanged.
- This edition supplies only Korean. Previous English core lessons are retained
  in Git history, not mixed into the new lesson sequence. The existing loader
  falls back to Korean when an unavailable language such as English is requested.
- IDE, runtime, examples, extension content, and product design are unchanged.

Before rebuilding, the previous copied tutorial under `build/local-debug/bin/Debug`
was moved to a local backup as well. CMake copies content without deleting obsolete
folders, so simply overwriting that deployed directory would leave duplicate lessons.
Apply the same complete-folder replacement when updating other existing builds or
portable distributions. The separate `C:\SmallCpp-Portable` installation was not
updated as part of this source integration.

## Measured validation

- 88 consecutively numbered lesson folders with unique IDs and valid UTF-8 metadata.
- All 264 `@code`, `@exercise`, and `@solution` references resolve; exercise and
  solution ordering is valid. Referenced local Markdown images, if any, exist.
- Built `SmallCppIDE` and `small_tutorial_programs` with the existing Qt 6.11.2 /
  GCC 13.1.0 kit: all **264 C++ programs compiled and linked** against the actual
  Small runtime. Examples, starters, and solutions are included in this count.
- A native smoke program using the unchanged `TutorialCatalog.cpp` loaded
  **88 core lessons plus 3 Image extension lessons**, found the first and last
  core lessons, and verified Korean loading and English-to-Korean fallback.

This checks source compilation and actual catalog loading. It does not claim
interactive window, sound, keyboard, mouse, or rendered tutorial UI validation.
The archive's `validation.json` records its author's earlier checks and is preserved
as source evidence, separate from the measurements above.

At the time of this content import, the historical full-suite failures in
`SETUP_VALIDATION.md` remained unresolved. Subsequent test maintenance updated
catalog, lesson, ID, and exercise assumptions: the current suite passes 29/29.
See [Regression validation](REGRESSION_VALIDATION.md) for measured coverage.

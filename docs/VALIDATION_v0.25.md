# Validation report — v0.25

## Executed in this environment

| Check | Result |
| --- | --- |
| Public API tests with GCC 14.2.0 | 65 checks passed |
| Public API tests with Clang | 65 checks passed |
| GCC AddressSanitizer + UndefinedBehaviorSanitizer, public API tests | 65 checks passed; no sanitizer errors reported |
| Reference/program examples, GCC translation-unit compilation | 19 / 19 passed |
| Reference/program examples, Clang translation-unit compilation | 19 / 19 passed |
| Existing reference coverage script | Passed for 12 reference files |
| Structural/layout checks | 24 / 24 passed |
| C++ lexical/delimiter inspection of IDE sources and Qt tests | No lexical/delimiter errors found |

Public tests now exercise inbound `std::string` conversion, value-copy behavior,
embedded zero bytes, and the absence of an implicit reverse conversion. Example
compilation includes all current String/Array/File/graphics/input/time/audio
APIs through the actual public header, without Qt headers in the learner source.

The coverage script checks token presence. It is **not** proof that every
possible overload or behavior is demonstrated. Structural and lexical scans
also do not replace a real Qt build or interactive tests.

## Not executed here

Qt GUI configuration was attempted but could not find `Qt6Config.cmake`.
The environment has no Qt development installation, and obtaining the missing
packages was unsuccessful. Therefore this report does NOT claim:

- a successful build/link of the full IDE or runtime on Windows;
- a run of `small_tabs_test` (17 newly added cases) or the existing Qt tests;
- interactive Windows validation of native dialogs, Ctrl+Tab focus handling,
  console spawning, audio or tab-close behavior.

The source and Qt tests are supplied for verification with the already-installed
Qt Creator/MinGW kit. No new non-Qt dependency is required by the application.
See `MULTITAB.md` for the target names and manual checks.

## Supporting results

`validation-v0.25/layout.txt`, `coverage.txt` and `example_compile.json` record
the executed source/compile checks. They contain no packaged object files or
machine-specific CMake caches. Older validation documents describe older
versions and should not be interpreted as current GUI test results.

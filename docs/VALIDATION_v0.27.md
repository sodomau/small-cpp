# Validation — Small C++ IDE v0.27

## Executed in this environment

| Check | Actual result |
| --- | --- |
| Tutorial catalog/resource integrity | Passed: 6 parts, 36 titles, 5 published lessons, exactly 10 exercises, 71 resource files |
| Runnable tutorial source inventory | 30 complete SmallMain programs: 10 teaching examples, 10 starters, 10 solutions |
| Tutorial programs with GCC | 30 compiled and linked; 50 input/output fixtures passed |
| Tutorial programs with Clang | 30 compiled and linked; the same 50 fixtures passed |
| Existing public API tests | 65 checks passed with GCC; 65 with Clang |
| AddressSanitizer + UndefinedBehaviorSanitizer | Public API test passed (65 checks), no sanitizer errors reported |
| Existing reference/program examples | 19 translation units compiled with GCC and with Clang |
| Existing example catalog/resource check | Passed, all 19 examples retained |
| Existing reference token checker | Passed for 12 reference files; token presence is not behavioral API coverage |
| Existing structural checks | 24 / 24 passed |
| Runtime and execution backend against v0.26 | Identical byte-for-byte; also preserved EditorDocument, ExampleCatalog and ExamplesBrowser implementation |

### What the tutorial execution tests actually do

`tools/verify_tutorial.py --compiler ...` extracts the existing console routines
(`Console`, `ReadLine`, `ReadNumber`, `Input*`) **verbatim** from the unchanged
`runtime/small_runtime.cpp`. A small non-GUI test main calls each lesson's real
`SmallMain()` and captures emitted stdout/stderr. Sources are compiled with the
public `small.h` force-included and SMALL_BEGINNER_MODE, as in the IDE.

The 50 fixtures cover expected lesson/solution output, complete runnable starters,
empty and UTF-8 names, invalid numeric input/retry, end-of-input, conditional
boundaries (0, 12/13, 19/20, 99/100), and loop/multiplication-table output.
Console echo supplied by the operating system is not expected C++ output.

This verifies the code and the existing console semantics in isolation. It does
**not** verify the Qt main, Windows console creation, rendering, native input,
resource compiler output, or the tutorial's on-screen layout.

`validation-v0.27/` contains machine-readable results and logs. Older reports
in the package are historical, not evidence of additional execution in v0.27.

## Added but not executed: Qt regression tests

`tests/test_tutorial.cpp` adds **20 Qt GUI/catalog cases**, covering:

- six-part/36-title catalog, five authored lessons, two exercises each;
- embedded loading independent of the working directory;
- Learn menu, lazy modeless browser construction and reuse;
- exact/read-only code previews and unrestricted lesson selection;
- new dirty Try tabs that preserve existing work, repeat-copy independence;
- all ten starter codes and complete solution-copy behavior;
- collapsed hints/solutions without grading or implicit completion;
- Next/Previous/Finish, persistent read marks and last lesson;
- safe handling of old/invalid settings and unavailable lessons;
- font/theme changes, related examples and read-only editing protection;
- save/cancel protection when closing an exercise copy.

The `small_tutorial_ui_test` target is wired into CTest when
`SMALL_BUILD_TESTS=ON`. The separate aggregate `small_tutorial_programs` target
builds/links all 30 lesson programs against the actual prebuilt Qt runtime.
These targets have **not** been built or run here.

## Environment limitation

A real CMake configuration was attempted. It stopped at find_package(Qt6)
because this environment has no Qt 6 development installation/Qt6Config.cmake.
Fetching development packages was also unavailable (repository DNS resolution).
Therefore the new Qt source, MOC/RCC output, whole IDE link, 20 new UI tests,
and prior Qt UI suites remain unverified here. This is not a Windows-tested
release and no compiled Windows executable is included.

## Windows acceptance pass

In Qt Creator, open `ide/CMakeLists.txt` with the existing Qt MinGW kit and build
SmallCppIDE. Keep a modified ordinary document open, choose Learn → Tutorial,
and use Try This Code. It must create an independent dirty tab. Run Lesson 3
and enter a name in the actual console. Try both exercise and solution copies;
Hint/Solution toggles must not modify editor text. Change Light/Dark and review
Korean text wrapping and code preview size at the actual DPI. Next and reopening
the IDE should retain only local read/last-lesson state.

For automated Qt tests, enable SMALL_BUILD_TESTS, build small_tutorial_ui_test,
and run it. Build small_tutorial_programs explicitly for real-runtime linking.

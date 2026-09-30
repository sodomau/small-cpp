# Validation — Small C++ IDE v0.26

## Executed here

| Check | Result |
| --- | --- |
| Catalog JSON, every source path, unique IDs, two groups, every qrc alias | Passed; 19 entries, 12 Reference + 7 Programs |
| Existing reference token-presence check | Passed for 12 reference files |
| Existing structural/layout checks | 24 / 24 passed |
| Public API tests, GCC 14.2.0 | 65 checks passed |
| Public API tests, Clang 17.0.0 | 65 checks passed |
| GCC AddressSanitizer + UndefinedBehaviorSanitizer public API tests | 65 checks passed; no sanitizer errors reported |
| All reference/program examples, GCC translation-unit compilation | 19 / 19 passed |
| All reference/program examples, Clang translation-unit compilation | 19 / 19 passed |
| Runtime source/header + BuildController hashes against v0.25 | Identical byte-for-byte |

The example compilations used the existing Small beginner flags and public
header (`-std=c++20 -DSMALL_BEGINNER_MODE -Wall -Wextra -Werror=parentheses`,
with `small.h` force-included). They check real example syntax and API use, not
the full Qt link or interactive behavior.

The catalog checker validates that the source files in the package and the
files embedded by the resource collection are the same set, without duplicate
IDs, source paths, or aliases. It does not execute Qt's resource compiler.
The older reference coverage script only checks token presence; it is not
proof of all overloads or behaviors being demonstrated.

## GUI tests added, not executed here

`tests/test_examples.cpp` adds **20 Qt regression cases** for catalog loading,
working-directory independence, browser reuse/preview, category selection,
opening examples without replacing user code, duplicate-open and tab reorder,
invalid IDs, Untitled naming, read-only editing protection, Try-copy isolation,
contextual controls, closing, cancelled saves, saved copies, duplicate-save
protection, appearance, and actual built-in example compile/link/run.

The existing multi-tab and Qt regression tests are preserved. New CMake target:
`small_examples_ui_test`. The optional Python integrity test is also registered
with CTest when Python is available. Python is not a runtime/build requirement
for normal IDE use.

## Platform limitations

A real CMake configuration was attempted, but this environment does not contain
`Qt6Config.cmake` or the Qt development packages. An attempt to obtain packages
could not resolve the repository host. Therefore the following are **not claimed**:

- compilation/linking of the new Qt browser, resources, IDE, or Qt test suite;
- execution of the 20 new GUI tests or existing multi-tab/Qt tests;
- visual inspection on Windows, high-DPI layout, native Save dialogs, or audio.

`validation-v0.26/` records actual check output and the failed Qt configuration.
Do not treat older validation reports or newly added test code as executed
results for this release.

## Windows acceptance check

Build `SmallCppIDE` with the existing Qt/MinGW kit, then:

1. Keep an edited ordinary tab open. Choose Examples, select Bouncing Ball,
   and Open. The ordinary tab and its unsaved changes should remain untouched.
2. The new tab should say `[Example]`, be read-only, and still allow Run.
   Try should create a separate editable Untitled copy with `*`.
3. Save/cancel that copy, switch back to the original example, and confirm its
   source is unchanged. Reopening the example should reuse the same tab.
4. Check Light/Dark and the saved font choice in the preview and new tabs.

With `SMALL_BUILD_TESTS=ON`, build/run `small_examples_ui_test`; build the
`small_examples` target explicitly to link all 19 reference/program examples.

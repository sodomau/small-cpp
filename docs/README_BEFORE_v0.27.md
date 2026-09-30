# Small C++ IDE v0.26 — Examples Browser

A native C++ learning environment. Each tab is an independent, single-file
program; this is not a multi-source project mode.

## Build and run

Unzip into a new folder. In **Qt Creator**, open **`ide/CMakeLists.txt`**, select
your existing **Qt 6 MinGW 64-bit kit** on Windows, and build/run **SmallCppIDE**.
The required application modules are still **Qt Widgets and Qt Multimedia**.
No new third-party library, WebEngine, browser runtime, or Python dependency is
needed to build/use the IDE.

The prebuilt Small runtime is compiled with the selected kit. Students' Run
operations compile only their source, with the existing lightweight `small.h`,
and link the prebuilt runtime. Compiler/Qt paths are recorded by CMake, as before.
A portable student distribution with a bundled compiler is not part of this
release; this is still the development project.

## New in this release

Choose **Examples...** on the menu bar.

- Browse **12 Reference examples + 7 Programs** in a separate, resizable window.
- See a description, concepts, controls/usage notes, and read-only code preview.
- **Open** adds a read-only `[Example]` tab; opening it again reuses that tab.
- **Run** works directly from the example tab.
- **Try** makes a dirty, editable Untitled copy without changing the original.
- **Save a Copy...** saves an example under a chosen filename and opens that copy
  as an ordinary tab. Cancelling leaves the original and all other tabs intact.
- Existing font/theme settings apply to the browser preview and example tabs.
- The catalog and example sources are embedded into the IDE at build time,
  so browsing does not depend on Internet access, the working directory, or a
  copy of the source-tree examples folder next to the executable.

The runtime API and BuildController are unchanged from v0.25.

## Existing editing behavior

- **Ctrl+N/O/S**: new tab, open file, save current tab.
- **Ctrl+Shift+S**: Save As (Save a Copy for a read-only example).
- **Ctrl+W** or the tab's close button: close the tab.
- **Ctrl+Tab / Ctrl+Shift+Tab**: switch tabs.
- **F5 / Shift+F5**: Run current tab / Stop.
- Each document has its own undo history, filename, modified `*`, and error mark.
- Save/Discard/Cancel guards modified documents, including new Try copies.
- The default code/Diagnostics font is Consolas 14; saved preferences override it.
- Student I/O uses the native Windows console. The IDE lower pane is Diagnostics.

## Example files and data files

Reference sources are in `examples/reference/`; motivational programs are in
`examples/programs/`. The browser uses the same sources, not independently
maintained copies.

File examples create/overwrite named data files. A read-only/unsaved example
run uses a temporary working folder. To keep data, choose **Try**, save the source
in your own folder, then Run. Read-only protects the built-in source; it does
not sandbox native C++ execution.

## Documentation and checks

- `docs/EXAMPLES_BROWSER.md`: UI, save behavior, resources, maintenance.
- `docs/VALIDATION_v0.26.md`: exact checks run and platform limitations.
- `docs/MULTITAB.md`: existing independent-document behavior.
- `tools/verify_example_catalog.py`: catalog/source/resource integrity.
- `tools/verify_examples.py`: existing token-presence reference coverage check.
- `tests/test_examples.cpp`: new Qt browser/tab regression tests.

With `SMALL_BUILD_TESTS=ON`, build/run `small_examples_ui_test` and the existing
Qt test targets. Build the optional **`small_examples`** target explicitly to
link all 19 examples. These test-only settings are not needed for normal IDE use.

Next planned phase: integrated tutorials. The browser is delivered here without
adding an empty Tutorial menu, permanent sidebar, or a project model.

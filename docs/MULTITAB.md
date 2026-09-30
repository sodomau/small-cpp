# Multi-tab contract — Phase 3E-1

## Scope

Several independent single-file programs can be open at once. Run builds only
one translation unit: the currently selected document plus the prebuilt Small
runtime. Open tabs do not imply a multi-file project. There is one active
compile/run process at a time; Stop still targets that process.

The example browser and read-only examples/Try copies are not implemented in
this phase. `EditorDocument` leaves a straightforward insertion point for the
next phase without introducing a project model.

## Identity and ownership

`QTabWidget` owns `EditorDocument` pages. Each page is a `CodeEditor` with its
own `QTextDocument`, undo history, filename and highlighter. There is no second
index-based array of document state to get out of sync when tabs move.

Qt does not delete the page when `removeTab()` is called, so closing a tab
explicitly deletes the removed page. `QPointer<EditorDocument>` guards the
origin of the most recent Run against deletion.

## File operations

Open paths are normalized and existing files use canonical paths. Windows path
comparison is case-insensitive. Already-open files activate their existing tab
without reloading and losing edits. Distinct files with the same basename
remain separate, and the tab tooltip shows the full path.

Save operates on a captured document, not a mutable current-tab index. `QSaveFile`
commits a complete UTF-8 document before the dirty marker is cleared or the
path is changed. Save As rejects a destination already owned by another open
tab. Existing disk files not open in another tab use the normal overwrite
confirmation provided by the file dialog.

Tab-close cancellation preserves the document. App shutdown first obtains all
save/discard decisions without removing any pages. Discard does not mark a
document clean; if a later prompt is cancelled, all not-yet-saved edits remain
present and marked. Successful earlier saves are not rolled back.

If compilation/execution is active when shutdown is accepted, the existing
asynchronous Stop path runs before the main window is destroyed.

## Run and diagnostics

Run captures the page identity, source snapshot, display name and saved path.
Unsaved pages get distinguishable build filenames. Tab changes, tab reordering
and Save As do not change the already-running snapshot or its working directory.

The diagnostics panel is shared and labelled with the most recent Run source.
A diagnostic never auto-switches tabs or highlights another document merely
because it has identical text. If the origin is edited, the message explains
that it describes the previous snapshot. If it is closed, the report remains
available with a closed-tab label; the executable may finish normally.

## Appearance

Consolas 14 is the default. Existing user-selected fonts remain respected.
Font/theme changes apply to every open editor and to future tabs. The
Diagnostics view uses the same font. Gutter widths, tab stops and line
highlights are refreshed after font/palette changes.

## Tests

`tests/test_tabs.cpp` contains 17 Qt tests covering document isolation, keyboard
shortcuts, duplicates, reordered saves/closes, filename collisions, save
cancellation, whole-window cancellation, theme/font defaults and async
compile/runtime diagnostic ownership.

In the existing Qt Creator kit, configure `SMALL_BUILD_TESTS=ON`. Build and run
`small_tabs_test`. The aggregate `small_examples` build target compiles and
links all 19 reference/program examples (it does not execute interactive games).
The examples now receive the same forced `small.h` include as the IDE.

From a terminal with the same Qt/MinGW environment, equivalent commands are:

```text
cmake --build <build-folder> --target small_tabs_test small_qt_test small_values_test small_examples
ctest --test-dir <build-folder> -C Debug --output-on-failure
```

The tests set `SMALL_TEST_DIALOGS` for controllable file dialogs and
`SMALL_TEST_NO_CONSOLE_PAUSE` so test programs do not wait for Enter on Windows.
Ordinary IDE launches do not set these switches.

Qt references used for implementation:
- https://doc.qt.io/qt-6/qtabwidget.html (page ownership and tab removal)
- https://doc.qt.io/qt-6/qpointer.html (guarded QObject pointers)
- https://doc.qt.io/qt-6/qsavefile.html (atomic save/commit behavior)

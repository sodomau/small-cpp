# Examples Browser — Phase 3E-2

## User workflow

Choose **Examples...** on the menu bar. There is no permanent example sidebar.
The browser is a resizable, modeless window, with two columns:

- Left: **Reference** (12 entries) and **Programs** (7 entries).
- Right: title, description, concepts, usage notes, and a syntax-highlighted,
  read-only code preview.

**Open** (or activating a leaf in the list) opens a read-only editor tab and hides
the browser. Reopening an example focuses its existing tab, even after the tab
was moved. The browser remembers its selection while this IDE instance is open.
No search, favorites, project explorer, or account system is introduced.

An example tab is labelled, for example, `Bouncing Ball [Example]`. The top-right
corner of the tab area shows **Read-only example / Try** only when an example is
selected. Normal source tabs have no extra controls taking up space.

**Run** executes the selected example without making an editable document.
**Try** makes a separate editable `Untitled-2.cpp *` (or the next available new
name). It copies the source, not the example identity or file path. The example
tab stays read-only and a new Try copy starts dirty so that closing it prompts
to save. All the usual tab, undo, font/theme, save, and run rules still apply.

## Saving and closing

- **Save / Ctrl+S** is disabled in a read-only example tab.
- **Save As / Ctrl+Shift+S** is labelled **Save a Copy...** on an example tab.
  It suggests the example's actual source filename. A successful save opens a
  normal, saved editable tab; it never converts or overwrites the example tab.
- Cancelling Save a Copy creates no new tab and changes no file.
- Saving over a path already open in a different editable tab is rejected,
  just as it was in v0.25.
- Closing the read-only example does not prompt. Closing a modified Try copy
  uses the existing Save / Discard / Cancel flow.
- Unsaved ordinary documents are not replaced or saved by opening an example.

## Execution and files

Examples are still independent, single-file C++ programs. They use the same
prebuilt runtime and asynchronous compiler as ordinary tabs.

The code resources do not have writable paths. The runner receives the source
snapshot and a normal `.cpp` name, not a `:/...` resource URL. An unsaved/built-in
run uses the existing per-run temporary working directory. Therefore the File
and Save Game examples do not overwrite data beside the shipped source files.
The browser and Diagnostics explicitly explain that these data files are
temporary. To keep files, choose Try, save the source in your own folder, then
Run; the existing runner uses the saved source's folder as its working directory.
The examples' notes name the files they may overwrite.

Read-only means that the **built-in source** is protected. It is not a sandbox:
a compiled C++ program still has the normal access of the user running it.

Diagnostics remain associated with the tab/snapshot that was passed to Run,
not whichever tab is selected when the compiler finishes. Read-only tabs also
support source highlighting. Closing/reopening an example during a run does not
rebind diagnostics to a new document with the same text.

## Resources and maintenance

`examples/catalog.json` contains metadata for the 19 reference/program examples.
`ide/SmallExamples.qrc` embeds that metadata and those exact `.cpp` files under
`:/small/examples/`. `small_ide_components` uses Qt AUTORCC, and ExampleCatalog
explicitly initializes the resource collection so that static-library linking
cannot discard it. There are no duplicated source strings in UI code and no
network request or runtime lookup of a source-tree directory.

The five older examples directly under `examples/` remain available in the
source package but are not duplicated in the browser; the reference/program
sets are its curated catalog.

To add a future built-in example:

1. Add its single-file C++ source under `examples/reference` or `examples/programs`.
2. Add a catalog entry (id = group/stem; source = group/stem.cpp).
3. Add a matching resource alias to `SmallExamples.qrc`.
4. Run `python tools/verify_example_catalog.py` and the existing example compile
   checks, then rebuild the IDE.

This is not the proposed third-party Extension system; that remains future work.

## Verification commands

The application does not require Python. The following optional development
checks use Python when available:

```text
python tools/verify_example_catalog.py
python tools/verify_examples.py
python tests/check_layout.py
```

The first checks metadata/resource integrity; the second is the older
**token-presence** API example check, not proof of every API behavior.

For the Qt regression suite, configure the project's existing
`SMALL_BUILD_TESTS=ON` option, then build `small_examples_ui_test`. This new suite
covers the browser, read-only tabs, Try, Save a Copy, theme/font, duplicate opens,
and a real compile/link/run of a built-in example through BuildController.
The existing `small_tabs_test` remains the multi-document regression suite.

The optional `small_examples` target separately builds/links all 19 examples.
It is excluded from the normal IDE build, so build that target explicitly.

See `VALIDATION_v0.26.md` for what was actually executed for this release.

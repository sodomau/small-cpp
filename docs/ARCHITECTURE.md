# Architecture

``` text
SmallCppIDE
├─ Editor / Learn UI
├─ BuildController → bundled MinGW
├─ DebugController → GDB/MI
├─ TutorialCatalog / TutorialBrowser
└─ Extension discovery → extension.json

Learner executable
├─ small_entry (small_main programs)
├─ small_runtime
├─ small_ide_pause (IDE Run/Debug only)
└─ optional extension libraries
```

## Runtime

`small_runtime` has no `main()`. `small_entry` supplies the hidden entry
point. Lifetime is explicit:
`initialize_small → small_main → shutdown_small`. Qt-dependent resources
such as audio are destroyed before `QApplication`.

In v0.76f the runtime itself does not register a console exit pause.
IDE Run and Debug directly link `small_ide_pause.o`, whose exit registration
implements IDE console-pause policy separately from runtime cleanup.

## Debugger

GDB/MI provides breakpoints, live breakpoint changes,
Continue/Over/Into/Out, source tracking, locals, user globals, readable
Small String values, separate learner console, and clean program-exit
handling. Ordinary Step Into filters Small/STL implementation frames.

## Tutorials

Filesystem content, not Qt resources:

``` text
tutorial/
├─ languages.json
└─ 01_hello/
   ├─ ko.md
   ├─ en.md (optional translation)
   ├─ *.cpp
   └─ images/
```

`NN_id` gives order/id. Markdown supplies title/part/goal/content.
Relative images resolve from the lesson directory.
The active core pack contains 88 Korean lessons, with three Image extension lessons.

## Portable deployment

A packaging-only `SmallDeployProbe` links the learner Qt module
superset. `windeployqt` runs on both IDE and probe so dependencies such
as Multimedia/plugins are discovered; the probe is removed from the
final package.

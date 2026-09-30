# Build and Packaging

## Build

Use the Qt MinGW 64-bit kit and build **Release** in Qt Creator.

## Package

Run:

``` text
package_release.bat
```

The package includes the IDE, bundled MinGW/GDB, Small runtime/entry
library, extensions, tutorial content, Qt import libraries, and Qt
runtime DLLs/plugins.

Current v0.76f builds also include `small_ide_pause`, linked by IDE Run/Debug.
See `DEVELOPMENT.md` for this machine's build and test commands.
When updating an existing output, replace the old tutorial directory completely
before copying the 88-lesson pack; copying on top can retain obsolete lessons.

## SmallDeployProbe

The IDE itself does not depend on every Qt module learner programs can
use. The packaging-only probe links the learner Qt superset;
`windeployqt` runs on both executables into the same output directory.
The probe is then deleted.

## Clean portability test

1.  Build and package.
2.  Close Qt Creator.
3.  Temporarily make local `C:\Qt` unavailable.
4.  Launch only packaged `SmallCppIDE.exe`.
5.  Test Print, Window, Sound, Image, and Debug.
6.  Restore Qt afterward.

A portable IDE is not enough: learner code must **compile → link → run →
load plugins → debug** without the developer Qt installation.

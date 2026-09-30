# Implementation notes

The runtime API and the learner program do not include Qt. `Window` owns an opaque
implementation, created only by `Open`. `String` and `Array<T>` remain normal
C++ value types. No friend functions are required.

CMake builds `small_runtime.cpp`, `small_sound.cpp`, and the fixed `small_main.cpp`
into one static archive. `small_sdk` copies that archive and the public header
beside the IDE. The IDE itself is not linked against this archive: it must not
pull in the learner's `main` or require a definition of `Main`.

The linker sees the learner object first, then the runtime archive, then the
Qt libraries recorded by the current CMake configuration. The archive member
containing `main` supplies the process entry point and calls the learner's `Main`.

CMake generates `SmallBuildConfig.h` separately for each build configuration.
It records the actual C++ compiler and the actual imported Qt linker files, not
an independently discovered compiler or the newest arbitrary Qt version.

The IDE executes only two build processes per Run: learner compilation and
linking. QProcess completion/error signals advance the pipeline. The public
header, precompiled runtime and toolchain use the same CMake kit.

`QTemporaryDir` isolates every invocation. No timestamp-based cache from an old
version in a shared Temp/SmallCppIDE directory is reused.

`QTextDocument::isModified()` is the single dirty-state source. `maybeSave()`
protects Close, New and Open. Failed/cancelled saves preserve the document and
cancel the destructive action. `QSaveFile::commit()` must succeed before the dirty
flag is cleared. Close during a build/run is deferred until asynchronous Stop
reaches Idle, so ordinary close does not destroy an active QProcess.

The Small user's `Main` remains on the GUI thread, matching the earlier runtime.
`IsOpen`, `Show`, `Sleep`, and blocking audio service GUI events. This is a small
teaching runtime, not a general-purpose scheduler. Arbitrary long computations
without an event-processing call can still make the learner's graphics window
unresponsive; the separate IDE stays responsive and can stop that program.

Reference APIs used:
- https://doc.qt.io/qt-6/qprocess.html
- https://doc.qt.io/qt-6/qsavefile.html
- https://doc.qt.io/qt-6/qaudiosink.html
- https://cmake.org/cmake/help/latest/command/file.html

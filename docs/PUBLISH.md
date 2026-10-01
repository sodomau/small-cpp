# Share a program with Publish

Publish creates a Windows x64 folder that runs without installing Small C++, Qt,
or a compiler. It is a local export; it does not upload your work to a website.

1. Open your program and choose **File → Publish…**.
2. Choose a **new folder** inside an existing parent folder. Existing folders
   are never overwritten.
3. Add any images, sounds, headers or data files your program needs. Selected
   files are copied beside `program.exe`; use their filenames in your code.
   Files with duplicate names or names used by the package are rejected.
4. Press **Publish**. The IDE builds the current editor contents, including
   unsaved changes, and opens the completed folder.
5. Test **START.cmd**, then share the **entire folder**, for example by compressing
   it into a ZIP. Sharing `program.exe` alone will not work.

`START.cmd` sets the working directory to the package folder and keeps the console
open after the program ends. `program.exe` itself has no IDE exit pause. This
keeps it usable from another console or application.

The package includes your current source in `source/program.cpp`, your compiled
object, Small libraries and Qt import libraries in `relink/`, and the matching
runtime license notices and source-access information in `licenses/`. Your code
is shared with the recipient. You decide your own program's license; the Small
MIT license does not automatically license your program. `relink/RELINK.cmd`
can relink the program using the matching MinGW compiler, without IDE pause
support. Compatible Qt DLLs can be replaced beside the executable.

Publish requires a prepared **Windows portable installation** with the matching
DLLs, plugins, import libraries and license notices. An incomplete development
build reports which file is missing. It uses the same compiler, SmallMain/manual
main selection and installed extension detection as Run. Export uses `-O2`.

The first version handles one source file and explicitly selected files with
flat filenames. It does not discover resource paths, copy an entire source
directory, support nested resource trees or third-party runtime dependencies,
create an installer, sign an executable or upload a release. Test the folder on
another Windows PC before distributing it widely. Files written by your program
need a writable location.

## Development validation

Prepare the DLL/plugin deployment, `qt/lib`, `LICENSE` and `licenses/` beside
`small_qt_test.exe` using the matching portable package, then run `small_qt`.
Publish integration tests execute SmallMain, ordinary main and Image/window
programs with only Windows System32 on PATH and no Qt plugin overrides. They
also check collisions, invalid source, cancellation, Unicode/space paths and
preservation of existing destinations. Those integration cases explicitly skip
when the prepared notices are absent; do not report skipped cases as tested.

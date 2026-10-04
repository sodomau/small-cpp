# Share a program with Publish

Publish creates a Windows x64 folder that runs without installing Small C++, Qt,
or a compiler. It is a local export; it does not upload your work to a website.

1. Open your program and choose **File → Publish…**.
2. Choose a **new folder** inside an existing parent folder. Existing folders
   are never overwritten.
3. Under **Extra Files — Optional**, choose **Add Files…** for any images,
   sounds, headers or data your program needs. You can add files in several
   batches and use **Remove** beside a file to leave it out. Selected
   files are copied beside the executable; use their filenames in your code.
   Files with duplicate names or names used by the package are rejected.
4. Press **Publish**. The IDE builds the current editor contents, including
   unsaved changes. When **Your program is ready!** appears, choose **Open Folder**.
5. Run the **exe**, then share the **entire folder**, for example by compressing
   it into a ZIP. Sharing only the exe will not work.

The executable follows your code's name: `MyGame.cpp` becomes `MyGame.exe`.
Names use English letters, numbers, hyphens and underscores. Other characters
are replaced with underscores; names with no usable characters become `Program.exe`.
The executable has no IDE exit pause. Console programs may close as soon as they
finish; run from an existing terminal when you need to read their output.
Resource paths are relative to the program's working directory, normally the
export folder when opened from File Explorer.

The package includes the executable, runtime DLLs/plugins, selected resources,
and matching license notices and library source-access information in `licenses/`.
Student source files, object files and relinking libraries are not added.
You decide your program's license; the Small MIT license does not automatically
license your program. Compatible Qt DLLs can be replaced beside the executable.

Publish requires a prepared **Windows portable installation** with the matching
DLLs, plugins, import libraries and license notices. An incomplete development
build reports which file is missing. It uses the same compiler, small_main/manual
main selection and installed extension detection as Run. Export uses `-O2`.

Single-file mode handles one source file and explicitly selected files with
flat filenames. [Project mode](PROJECT_MODE.md) builds all included source files
and preserves nested resource folders. Neither mode discovers third-party
runtime dependencies, creates an installer, signs an executable or uploads a
release. Test the folder on
another Windows PC before distributing it widely. Files written by your program
need a writable location.

## Development validation

Prepare the DLL/plugin deployment, `LICENSE` and `licenses/` beside
`small_qt_test.exe` using the matching portable package, then run `small_qt`.
Publish integration tests execute small_main, ordinary main and Image/window
programs with only Windows System32 on PATH and no Qt plugin overrides. They
also check collisions, invalid source, cancellation, Unicode/space paths and
preservation of existing destinations. Those integration cases explicitly skip
when the prepared notices are absent; do not report skipped cases as tested.

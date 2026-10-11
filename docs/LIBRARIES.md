# Libraries and file build options

Choose **Tools → Libraries…** to search pkg-config modules and select the ones
used by your program. Selection writes a declaration; it does not install a
package. The dialog edits `small.project` while a project is open, otherwise the
current editable file. Cancel leaves declarations unchanged.

For one file, put a JSON object in consecutive `//@` lines at the very beginning:

```cpp
//@ {
//@   "libraries": ["fmt"],
//@   "compiler_options": ["-O2"]
//@ }

#include <fmt/format.h>

void small_main()
{
    print(fmt::format("Hello, {}!", 42).c_str());
}
```

The first blank or ordinary line ends the settings block. Later `//@` comments
are ordinary comments. The collected text must be one JSON object. Supported
keys are `libraries`, `include_paths`, `library_paths`, `compiler_options`, and
`linker_options`; each is an array of nonempty strings. Paths are relative to the
saved file's directory. Output paths and compilation stages remain IDE-controlled.
For projects, use these same keys in `small.project`; per-file declarations are
not applied on top of project settings.

`libraries` contains **pkg-config module names**, such as `fmt`, `fftw3`, or
`eigen3`, rather than pacman package names. Existing project settings using
explicit archive paths or names resolved in `library_paths` remain supported.

Run, Debug, and Publish check the actual environment with `pkg-config --exists`.
If a module is absent, Small finds its UCRT64 package in the bundled catalog,
asks you to choose when several packages provide it, and asks before installing
packages and their dependencies. Pacman progress/errors appear in Library
Console. Cancelling installation approval or a failed installation stops the
build but keeps the declarations. Stop during a running installation waits for
the package transaction to finish before cancelling the build.

After installation, Small rechecks the modules and uses `pkg-config --cflags`
and `--libs` for compilation and linking. pkg-config is included in newly
prepared environments; an older environment may require its installation first.

**Update List** refreshes pacman's file database and rebuilds the module catalog.
It does not install, remove, or upgrade libraries. No automatic update runs at
IDE startup. The refreshed catalog is saved in the user's application-data
directory; package-installed state is always queried from the active environment.
If repository metadata or the toolchain needs updating, use MSYS2 Terminal and
its normal update procedure. Small does not silently perform a system upgrade.

## Sharing programs

Publish inspects normal and delay-loaded PE imports recursively, includes
non-system DLL dependencies, and fails for unresolved dependencies or
conflicting DLL versions. Test the published folder with Small/MSYS2 absent
from PATH. DLLs loaded by computed names, external plugins, and their data files
cannot be discovered from the import table; add them as resources explicitly.

For pkg-config libraries, Publish also copies available installed UCRT64 license
notices and writes package-version/source references in
`licenses/installed-libraries.json`. This inventory is an environment snapshot,
not a minimal list of libraries used by the program. Additional libraries may
have redistribution requirements beyond supplying DLLs and notices; review
their terms before sharing. Existing Small/Qt notices remain in the export.

## Maintainer catalog generation

Run `tools/generate_msys2_pkgconfig_map.py` in an MSYS2 environment with Python
and redirect stdout to `ide/msys2_pkgconfig_map.json`. Status and pacman messages
go to stderr. The IDE's Update List implements the same UCRT64 `.pc` scan in Qt,
so this feature does not require Python in learner environments.

# Windows portable release preparation

The first public Windows package targets x86-64 Windows and is published as an
early preview. Do not mark the manual release checklist complete without doing
the individual checks on a machine without developer tools.

## Build and notices

For v0.76.16 and later, use the coherent MSYS2 UCRT64 kit and minimal environment
described in [DEVELOPMENT.md](DEVELOPMENT.md). Prepare notices with
`tools/prepare_msys2_notices.py --environment <source-env> --package <prepared-package>
--sources build/<sources> --notices build/<notices> --version <version>`.
This collects exact MSYS2 source-only packages with PKGBUILD recipes and patches
for both the learner environment and deployed IDE libraries. Pass that notice
directory and `-Msys2Dir <source-env>` to the release packager. Use
`tools/package_zip.py` to preserve empty runtime directories in the portable ZIP,
and publish the source ZIP and checksums alongside the installer and portable ZIP.

The instructions below retain the original Qt-only release's preparation details;
its compiler sources and notices do not cover the MSYS2 distribution.

Build Release with the matching Qt MinGW kit, as described in DEVELOPMENT.md.
Set `Python3_EXECUTABLE` explicitly when Python is not on PATH so the full test
suite is registered. Copy/deploy the test DLLs and plugins as in that document.

Prepare a source directory under `build/` containing the exact upstream archives
for every deployed component. The first package uses Qt 6.11.2 qtbase,
qtmultimedia and qtsvg source archives; their `.tag` values must match the
installed SPDX records. Preserve Qt configure options, summaries and SBOMs.

The toolchain is MinGW-W64 GCC 13.1.0, POSIX/SEH/MSVCRT, rt_v11-rev1.
Preserve its installed `licenses/` directory and `build-info.txt`, which records
dependency versions, build options and 49 patch names. The source bundle includes
all the dependency archives plus the following pinned source snapshots:

- mingw-builds scripts/patches at `7ff96692a8032d893781523b311ac9b6cbbda0a1`
  (develop at the 2023-05-24 build date; all recorded patches are present).
- cpython-mingw at `12d1cb5b7c60901e36163b3e0599f11703c4946a`, explicitly recorded
  in the toolchain's build-info.
- mingw-w64 v11.x at `c3e587c067a00a561899d49d3e63a659e38802ec`, the upstream
  branch snapshot at that build date. The vendor build-info repeats stale URL
  values for several runtime/tool entries; do not use those URL fields alone.

Run the notice assembler with Python 3.11 or later:

```powershell
python tools/prepare_release_notices.py --sources build/release-sources --qt C:/Qt/6.11.2/mingw_64 --compiler C:/Qt/Tools/mingw1310_64 --output build/release-notices
```

Copy `docs/RELEASE_SOURCE_ACCESS.md` to the notice directory as `SOURCE_ACCESS.md`.
Review the source inventory and archive hashes, source notices, installed
toolchain notices and Qt SBOMs before packaging. Publish the corresponding
source archive on the same release page as the executable package.

## Package

```powershell
./package_release.bat -BuildDir build/local-release/bin/Release -OutputDir build/SmallCpp-v0.76.6-Windows-x64 -NoticesDir build/release-notices
```

The packager requires a fresh destination under `build/` and a prepared notice
directory. It preserves existing packages, includes the compiler/debugger,
runtime, Image extension, tutorials, Small MIT license and `START_HERE.md`.
It uses native Windows multimedia for Small's generated PCM sound API and omits
FFmpeg, software OpenGL and the system D3D compiler. Verify the final package
contains no deploy probe or QA executables, personal settings or developer paths
in its notices. Generate SHA-256 hashes for release archives.

Validate with the package's own compiler, linker libraries, plugins and runtime,
with Qt/toolchain development paths removed from PATH. Record this separately
from a truly clean Windows PC test. Publish incomplete clean-machine/manual QA
status explicitly in the release notes.

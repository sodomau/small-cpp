# Sources and library replacement — Small C++ v0.76.6

Download `SmallCpp-v0.76.6-ThirdPartySources.zip` from the same GitHub release:
https://github.com/sodomau/small-cpp/releases/tag/v0.76.6

This is provided without charge alongside the Windows binary ZIP. It contains
Qt 6.11.2 qtbase/qtmultimedia/qtsvg, GCC 13.1.0, binutils 2.39, GDB 11.2,
their toolchain dependencies, upstream mingw-builds scripts and patches,
the pinned cpython-mingw and mingw-w64 snapshots, build records and SHA-256
source inventory. Source archives are retained intact with their original
notices. Source URLs and pinned revisions are recorded in the bundle.

Small C++'s own corresponding source is available using GitHub's **Source code
(zip)** or **Source code (tar.gz)** asset on that release, under the MIT License.

## Qt rights

This application uses Qt's LGPL-3.0 libraries through replaceable DLLs. Qt and
its third-party components are not covered by Small C++'s MIT license.
The complete license texts are under `source-notices/` in this directory,
including the Qt source `LICENSES/` directories and GPL-3.0/LGPL-3.0 texts.
Qt component copyright and attribution information is in `THIRD_PARTY.txt`,
`qt-sbom/` and the source notices.

You may modify and replace compatible Qt libraries, and reverse engineer or
debug this application for that purpose. No additional license term in this
package restricts those rights. No activation, signing check, or installation
secret is required to run a modified build.

Close Small C++ before replacing its Qt DLLs/plugins with compatible x86-64
MinGW builds. Preserve matching versions and ABI across the Qt libraries.
To rebuild Qt, use the supplied Qt sources and their build instructions;
the installed kit's configure options/summaries are included in `qt-sbom/`.
To rebuild Small C++ or relink it with another Qt kit, follow
`docs/DEVELOPMENT.md` in Small's source archive. Configure from `ide/`, point
`CMAKE_PREFIX_PATH` at your replacement Qt kit, and build with a matching compiler.

## Toolchain rights and rebuild information

GCC, binutils, GDB and other tools retain their respective GPL, LGPL, BSD and
other terms. Their license texts are in `toolchain/`; the full vendor build
record is `toolchain-build-info.txt`. Runtime-library exceptions do not change
the licenses of compiler/debugger programs.

The source bundle includes all recorded patches in the mingw-builds tree. Its
`build` script runs in an MSYS2 build environment. Follow that project's README
and use the options at the beginning of the supplied vendor build record
(`gcc-13.1.0`, x86_64, POSIX, SEH, MSVCRT, runtime v11, revision 1). Dependency
build configurations are recorded individually in the same file. The Python
source revision is pinned by the vendor; the mingw-w64 and mingw-builds trees
are snapshots of the vendor's upstream branches at its recorded build date.

If an archive is unavailable or you find a source/notice mismatch, report it at
https://github.com/sodomau/small-cpp/issues so that the release can be corrected.

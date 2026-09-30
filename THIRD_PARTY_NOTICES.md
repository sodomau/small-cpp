# Third-party components and release preparation

Small C++ project materials are licensed under the [MIT License](LICENSE).
That license does not replace the licenses of external libraries, tools,
plugins, or their dependencies. This file is an inventory and preparation
guide, not a complete set of notices for a binary distribution.

## Project materials

The project license covers the Small-owned IDE, runtime, extensions, tests,
tools, example programs, tutorial text, documentation, and logo/icon assets,
except material carrying a separate notice.

The repository was imported from the author's supplied IDE archive and
tutorial pack. The author reports that the code, tutorials, and logo were
created with the assistant. This is the provenance recorded for this license
decision, not an independent audit of the imported archives. Preserve any
third-party notices discovered later and review their compatibility before
redistributing the affected material.

## External components

| Component | How it is used | License review for distribution |
| --- | --- | --- |
| Qt Core, Gui, Widgets, Multimedia | IDE and learner runtime dependencies | Verify the licenses of the exact kit, modules, plugins, and third-party components shipped. Qt offers LGPL/GPL and commercial licensing options; not every component has the same terms. |
| FFmpeg and other Qt plugin dependencies | May be deployed by Qt Multimedia and deployment tools | Inspect the actual package; include notices, license texts, and corresponding source access as required for the exact binaries. |
| MinGW-w64 toolchain, GCC, runtime libraries, binutils, GDB, and other bundled tools | The portable packaging script copies the entire selected toolchain | Inventory the whole copied tree. Each component retains its own terms. GCC runtime exceptions do not waive the conditions for redistributing compiler/debugger binaries. |

The `.a` suffix alone does not establish static linking: MinGW Qt kits also
use `.a` import libraries for DLLs. Check actual dependencies when preparing
a release. Small's own static runtime archives are distinct from Qt's linking
mode.

## Before publishing a portable binary package

The existing `tools/package_release.ps1` deploys Qt runtime files and plugins,
copies Qt linker libraries, and copies the MinGW toolchain. It does not yet
assemble a complete license/notice bundle or source distribution.

1. Record exact versions and all shipped files, including plugin dependencies
   and the toolchain's auxiliary programs. Use the Qt kit's SBOM/attribution
   files where available, and inspect the actual deployment output.
2. Include Small's `LICENSE` and the complete applicable third-party license
   texts and copyright/attribution notices in the package.
3. For each component requiring corresponding source, provide the exact source
   and necessary patches/build information through a method permitted by its
   license. A generic upstream homepage is not evidence of compliance.
4. If using LGPL Qt, document library use and recipients' rights, provide the
   required source access, and preserve the ability to replace/relink the
   libraries as required. Review static linking separately if introduced.
5. Review GCC/GDB/binutils and the rest of the copied toolchain independently;
   bundling a development tool is different from distributing its output.
6. Verify the final archive contains the approved notices and source-access
   instructions before publishing it. Do not describe this inventory as a
   completed binary license audit.

## References

- [Qt licensing](https://doc.qt.io/qt-6/licensing.html)
- [Qt LGPL obligations](https://www.qt.io/development/open-source-lgpl-obligations)
- [Qt Multimedia FFmpeg attribution](https://doc.qt.io/qt-6/qtmultimedia-attribution-ffmpeg.html)
- [GCC licensing](https://gcc.gnu.org/onlinedocs/libstdc++/manual/license.html)
- [GDB copying conditions](https://sourceware.org/gdb/current/onlinedocs/gdb.html/Copying.html)

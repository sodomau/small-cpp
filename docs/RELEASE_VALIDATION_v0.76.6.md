# First public Windows preview validation — 2026-09-30

Built on Windows 11 with Qt 6.11.2, MinGW-w64 GCC 13.1.0 and CMake/Ninja,
using Release mode under `build/local-release`.

- Release build and portable packaging completed.
- Full CTest suite: **30/30 passed** after the String debugger fix.
  The final quote/error-handling refinement also passed the live String
  regression (text with embedded quotes, empty String, resume and exit).
- Portable MainWindow, catalog loading, Run and Debug controllers were
  exercised with the application directory set to the portable package.
  Core + Image tutorials: **91 lessons** (88 core + three Image).
  Embedded examples: **24**.
- Print, Window, generated Sound and Image save/load programs compiled,
  linked and exited successfully through the packaged build/run path.
- A live bundled GDB session reached an initial breakpoint, displayed local
  and global numbers plus String text, and exercised live breakpoint changes,
  Over, Into, Out, Continue and clean termination.
- Independently compiled and ran five programs using only package paths:
  Print, manual main, Window, Sound and Image save/load. Their environment
  PATH contained only the package, its compiler and Windows system folders.
  All printed the expected marker and exited successfully, with no development
  Qt/toolchain paths supplied to compilation, linking or execution.
- Package includes Small MIT LICENSE, first-use instructions, 409 extracted
  source-notice files, the installed toolchain notice tree, Qt SBOMs and build
  records, source-access instructions and a hashed inventory of 29 source archives.
  Qt source `.tag` values match the installed kit's source revisions.
  All 49 toolchain patches recorded in build-info are present in the supplied
  mingw-builds snapshot. Corresponding source archives are release assets.
- The deployed native Windows multimedia backend supports Small's generated
  PCM sound API. FFmpeg, software OpenGL, system D3D compiler, deploy probe and
  temporary QA executables are excluded.

## Limits

This is an unsigned **pre-release**, not completion of the entire manual
RELEASE_CHECKLIST.md. A separate Windows PC with `C:\Qt` unavailable has not
been tested. The host already has Qt installed; removing development paths
from the direct program environment tests packaging dependencies but is not
equivalent to a clean PC. Audible output quality, all interactive tutorial
actions and every mouse/keyboard scenario have not been manually certified.

The debugger String buffer expression targets the supported GCC/libstdc++ kit.
Toolchain build scripts and mingw-w64 sources are upstream snapshots at the
vendor's recorded build date; Python has the exact revision recorded by the
vendor. Source/notice assembly and archive inventory checks are recorded here;
they are not a claim of an independent legal audit of all imported material.

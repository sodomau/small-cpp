# Development workflow

The development repository was imported from
`SmallCpp-IDE-v0.76f-ide-pause-config-fix.zip` on 2026-09-30.
The archive's internal `SmallCpp-IDE-v0.65/` directory name is historical;
its README identifies the contents as v0.76f. The original archive is preserved.

The later `SmallCpp-IDE-v0.76i-origin-story.zip` (CMake version 0.76.9)
was reconciled on 2026-09-30. Its origin story, public guides, directly linked
IDE pause object and packaged documentation are integrated with the current
themes, debugger fixes, licensing and Small Steps tutorial pack.

The core tutorial was subsequently replaced with the user's latest
`SmallCpp-Core-Tutorial-KO-Small-Steps.zip`: 88 Korean lessons. Keep it as a
complete content set rather than merging older lesson folders into it.
Companion documents live in `docs/tutorial-small-steps/`; see
`TUTORIAL_SMALL_STEPS.md` for integration and validation.

## Repository layout

- `ide/`: Qt desktop IDE and the main CMake entry point.
- `runtime/`: Small public API, runtime, entry point and IDE pause support.
- `extensions/`: manifest-driven extensions, starting with Image.
- `examples/`, `tutorial/`: learner examples, lesson prose and assets.
- `tests/`, `tools/`: regression tests, validation and release packaging.
- `docs/`: philosophy, design notes, historical validation and development guidance.
- `validation-v0.26/`, `validation-v0.27/`: preserved historical reports.
- `build/`: ignored local output, not a source directory.

The existing source layout is preserved. No top-level CMake wrapper is needed:
configure from `ide/`.

## Windows build

Use a matching Qt MinGW 64-bit kit, not MSVC. This machine has Qt 6.11.2 and
MinGW 13.1.0. In Qt Creator, open `ide/CMakeLists.txt`, select that kit, and keep
the build directory under `build/`. Enable `SMALL_BUILD_TESTS` for regression tests.

Equivalent PowerShell commands from the repository root:

```powershell
$env:PATH = 'C:\Qt\Tools\mingw1310_64\bin;C:\Qt\6.11.2\mingw_64\bin;C:\Qt\Tools\Ninja;' + $env:PATH
& C:\Qt\Tools\CMake\bin\cmake.exe -S ide -B build/local-debug -G Ninja -DCMAKE_BUILD_TYPE=Debug -DSMALL_BUILD_TESTS=ON -DCMAKE_PREFIX_PATH=C:/Qt/6.11.2/mingw_64 -DCMAKE_CXX_COMPILER=C:/Qt/Tools/mingw1310_64/bin/g++.exe -DCMAKE_MAKE_PROGRAM=C:/Qt/Tools/Ninja/ninja.exe
& C:\Qt\Tools\CMake\bin\cmake.exe --build build/local-debug --parallel 4
& C:\Qt\6.11.2\mingw_64\bin\windeployqt.exe --release --no-translations build/local-debug/bin/Debug/small_qt_test.exe
Copy-Item -LiteralPath C:\Qt\6.11.2\mingw_64\plugins\platforms\qoffscreen.dll,C:\Qt\6.11.2\mingw_64\plugins\platforms\qminimal.dll -Destination build/local-debug/bin/Debug/platforms
Get-ChildItem -LiteralPath build/local-debug/bin/Debug -Filter '*.dll' | Copy-Item -Destination build/local-debug
$env:QT_PLUGIN_PATH = 'C:\Qt\6.11.2\mingw_64\plugins'
$env:PYTHONUTF8 = '1'
& C:\Qt\Tools\CMake\bin\ctest.exe --test-dir build/local-debug --output-on-failure
```

If Python is not on PATH, pass its executable with `-DPython3_EXECUTABLE=...`.
Run Python validation in UTF-8 mode: `python -X utf8 tools/verify_build_config.py`.
Qt GUI tests use the offscreen platform configured in CMake. Keep Qt and MinGW
bin directories on PATH for runtime DLL discovery.
This Qt installation supplies release Qt DLLs even when the application is built
with debug symbols, hence `windeployqt --release`. The local DLL deployment also
supports restricted test processes; all deployed files remain ignored under `build/`.

The bundled Git on this machine has its HTTPS helper under `clangarm64/bin` rather
than the default helper directory. If Git reports `remote-https is not a git command`,
set `GIT_EXEC_PATH` for that shell to the installed Git directory containing
`git-remote-https.exe`. With a normal Git for Windows installation this workaround
is unnecessary. GitHub authentication is handled by Git Credential Manager; never
put a token into the repository or remote URL.

Examples and tutorial programs have optional compilation targets:

```powershell
& C:\Qt\Tools\CMake\bin\cmake.exe --build build/local-debug --target small_examples small_tutorial_programs --parallel 4
```

Build Release separately under `build/local-release`. The existing
`package_release.bat` / `tools/package_release.ps1` workflow produces a portable
distribution. Publish binaries as GitHub Release assets when requested, not as
source commits. Small-owned project materials use the MIT license; see
`../LICENSE` and `../THIRD_PARTY_NOTICES.md`. A portable binary release also
requires the applicable external license notices and source-access provisions;
the current packaging script does not complete that preparation automatically.

## Change and commit workflow

```text
Check status and recent commits
  -> change one coherent feature or fix
  -> build and run relevant tests
  -> review working diff and staged diff
  -> commit explicit files with a meaningful message
  -> push when authorized
```

Before work: `git status --short --branch`, `git log -5 --oneline`, `git diff`.
For separate work, create a short descriptive branch such as `fix/tutorial-links`.
Before committing: `git diff --check`, stage selected paths, then
`git diff --cached --stat` and `git diff --cached`.
Examples: `fix: restore tutorial navigation`, `feat: reload external theme`,
`docs: clarify small_main lifecycle`.
Never commit unrelated edits or silently rewrite history.

## Continuous work in Codex

Add this repository folder as a local project and use it as the primary folder.
start future development chats from that project so they use the same code and
root `AGENTS.md`. This setup chat itself is projectless; saving the repository
does not register it automatically in the app.
Official project guidance: https://learn.chatgpt.com/docs/projects

## Baseline validation

The untouched v0.76f archive initially fails the test-enabled build because
`tests/test_qt.cpp` uses `DetectEntryPoint` without including `EntryPoint.h`.
The import commit preserves this baseline; a separate test-only fix adds the include
and updates extension detection calls to supply discovered installed extensions.

Historical validators have now been updated for the external lesson packs and
current Learn windows. CTest runs all 20 Python validators alongside the native
tests and validator regression cases: 29/29 checks pass. `SETUP_VALIDATION.md`
preserves the import baseline; `REGRESSION_VALIDATION.md` records current results.

For all 264 tutorial builds and six representative real-runtime output checks:

```powershell
& C:\Qt\Tools\CMake\bin\cmake.exe --build build/local-debug --target small_tutorial_programs --parallel 4
Get-ChildItem -LiteralPath build/local-debug/bin/Debug -Filter '*.dll' | Copy-Item -Destination build/local-debug/bin/Debug/tutorial
python -X utf8 tools/verify_tutorial.py --build-dir build/local-debug --cmake C:/Qt/Tools/CMake/bin/cmake.exe --report build/local-debug/tutorial-validation.json
```

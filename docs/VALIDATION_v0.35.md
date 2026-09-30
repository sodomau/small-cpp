# Validation — v0.35

- `windows.h` occurs in exactly one runtime source: `small_platform_win.cpp`.
- `small_runtime.cpp` contains no Win32 header or direct Win32 API call.
- Generic non-Windows platform hook compiles with the available host compiler.
- Tutorial manifest/resource integrity passed.
- Example catalog and learner API coverage verifiers passed.
- Final MinGW/Qt Windows build must be run in the user's Qt Creator kit; that environment is what originally exposed the Win32 macro collision.

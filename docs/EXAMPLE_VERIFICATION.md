# Current note (v0.25)

With `SMALL_BUILD_TESTS=ON`, the aggregate `small_examples` target builds and
links all examples. Each example target now force-includes `runtime/small.h`,
just as the IDE does. Token coverage remains a lightweight check, not a full
semantic-coverage proof. See `VALIDATION_v0.25.md` for current test results.

---

# Phase 3D — Example Verification

## Policy
- Coverage tracks learner-facing vocabulary, not every technically public C++ member.
- Reference examples are the authoritative coverage set.
- Program examples are motivational and are not required to cover APIs.
- Every shipped example must compile.

## Automated coverage
Run:

```text
python tools/verify_examples.py
```

Current result: `Reference coverage OK: 12 files
All learner-facing API groups and learner enum values are represented.`

## Compile verification
This package was compile-checked (translation unit only) for all 19 reference/program `.cpp` files with `g++` against `small.h`.

Full link/run verification for Qt examples requires the Qt MinGW kit. With `SMALL_BUILD_TESTS=ON`, CMake now creates an excluded build target for every example linked against the actual `small_runtime`. This is the Windows/Qt acceptance check to run in Qt Creator.

## Phase 3D audit fixes
The audit found and fixed missing learner coverage for:
- explicit `FileMode::Read`
- `File::IsOpen`
- text `File::InputInt` and `InputReal`
- all built-in named colors
- `Window::Close`

This is exactly why coverage is automated before IDE integration.

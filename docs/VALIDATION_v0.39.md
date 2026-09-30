# Validation — v0.39

- Graduation namespace policy verifier passed.
- Host compiler acceptance:
  - unqualified Small names + `SMALL_BEGINNER_MODE`: compile;
  - unqualified Small names in real `main()` without beginner mode: intentionally fail;
  - `Small::`-qualified names in real `main()`: compile.
- Manual-main CMake regression tests no longer define `SMALL_BEGINNER_MODE`.
- Tutorial, collision, build-config, example catalog, and learner API verifiers passed.

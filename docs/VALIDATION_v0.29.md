# Validation — v0.29

## Checked in this environment
- Example catalog/resource integrity: passed (19 examples).
- Tutorial content integrity: passed (36 catalog lessons, 5 published, 30 C++ tutorial sources).
- Learner API/reference coverage verifier: passed.
- Header compile checks for `InitializeSmall()`, `InitializeSmall(argc, argv)`, manual `main()`, and ordinary standard C++ `main()`: passed with the available host C++ compiler.

## Added Windows/Qt regression coverage
The Qt test suite now checks:
- lexical entry detection for real `main()` definitions;
- comments, string literals, declarations and namespace-nested `main` do not trigger manual-main mode;
- explicit `main()` wins if `SmallMain()` is also present;
- BuildController can compile, link and run a learner-owned `main()` with `InitializeSmall(argc, argv)`.
CMake also builds/runs manual-main tests for both default and argc/argv initialization when `SMALL_BUILD_TESTS=ON`.

## Environment limitation
This container does not provide the Qt development kit used by the Windows IDE, so the complete Qt/MinGW link/run suite cannot be executed here. Run `SMALL_BUILD_TESTS=ON` in the Qt Creator MinGW kit for final acceptance.

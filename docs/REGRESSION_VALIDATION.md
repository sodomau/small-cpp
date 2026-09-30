# Regression validation — 2026-09-30

The current Windows Debug build and CTest suite pass **29/29 checks**, with zero
failures. Environment: Qt 6.11.2, MinGW GCC 13.1.0, Ninja, C++20; Qt UI tests use
the offscreen platform. Commands are documented in `DEVELOPMENT.md`.

## Updated expectations

- External core lesson folders replace obsolete JSON catalogs and Qt resources:
  88 core lessons, 264 C++ files, and Korean fallback for unavailable translations.
- Learn tests locate independent top-level browser windows, release them between
  cases, and check 91 total lessons, 94 exercises, and 24 examples including Image.
- Validators use current lesson paths, metadata, API names, and UTF-8 explicitly;
  the obsolete debugger version assertion is removed while integration checks remain.
- The manual-main fixture uses the actual namespaced initialization/print/shutdown API.
- All 20 Python validators run through CTest. Six validator regression cases check
  translation fallback and rejection of missing sources, orphan solutions, unsafe
  paths, unknown related examples, and duplicate lesson numbers.

## Small implementation fixes found by tests

Settings construction now honors the configured QSettings backend. Normal runs
retain native settings under the same organization/application names; tests use
isolated temporary INI files instead of the Windows registry.

Appearance changes preserve a document's existing modified state. Tests check
both clean read-only previews and edited copies across theme changes.
Runtime APIs, lesson content, source layout, and product architecture are preserved.

## Additional tutorial validation

All **264 core programs compiled and linked** against the actual Small runtime.
Six representative console fixtures also passed exact exit-code, stdout, and
stderr checks. These fixtures replace obsolete lesson-output fixtures; they are
representative coverage, not execution of every lesson. The local machine-readable
report is `build/local-debug/tutorial-validation.json`.

Qt test logs are retained under the ignored build directory. This validation
covers automated offscreen UI behavior and does not establish interactive sound,
mouse/keyboard behavior, a live GDB session, or release-package operation.
The earlier failures remain documented as history in `SETUP_VALIDATION.md`.

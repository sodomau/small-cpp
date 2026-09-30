# Small C++ IDE

Small C++ is an educational C++ environment: **simple C++, not a new
language**. It hides accidental setup/implementation complexity while
preserving real programming concepts and conventional debugger behavior.

Documentation imported from `SmallCpp-Documentation-v0.76b.zip` and adapted
to the current v0.76f source plus the Korean 88-lesson Small Steps tutorial.
The source ZIP is preserved in OneDrive; earlier repository documents remain in Git history.

Current single-file baseline (v0.76f): compile/run, Window
graphics/input, sound, files/timing, Image extension, Examples, API
Reference, GDB/MI debugger, portable MinGW/Qt packaging, and external
Korean Small Steps core tutorials. The loader continues to support translations
and default-language fallback; this core content pack supplies Korean only.

## Documentation

-   `GETTING_STARTED.md` --- first use.
-   `SMALL_CPP_GUIDE.md` --- learner-facing programming model.
-   `DESIGN.md` --- philosophy, decisions, scope, and future direction.
-   `ARCHITECTURE.md` --- technical structure.
-   `BUILD_AND_PACKAGING.md` --- build and portable release.
-   `EXTENSIONS_AND_TUTORIALS.md` --- authoring extensions/tutorials.
-   `RELEASE_CHECKLIST.md` --- regression checks.
-   `DEVELOPMENT_HISTORY.md` --- major milestones.

Single-file mode is feature-complete for now. The next major direction
described by the supplied design document is Project Mode. Its design remains
open and must be discussed before implementation.

For current build commands and Git workflow, read [DEVELOPMENT.md](DEVELOPMENT.md).
For measured checks and remaining failures, read [SETUP_VALIDATION.md](SETUP_VALIDATION.md)
and [TUTORIAL_SMALL_STEPS.md](TUTORIAL_SMALL_STEPS.md).
The full design manifesto remains [PHILOSOPHY.md](PHILOSOPHY.md);
`DESIGN.md` is a complementary overview.

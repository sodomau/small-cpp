# Release Checklist

## Build/package

-   [ ] Release build succeeds.
-   [ ] `package_release.bat` succeeds.
-   [ ] `SmallDeployProbe.exe` is absent from final package.

## Clean portability (`C:\Qt` unavailable)

-   [ ] IDE starts.
-   [ ] Print compiles/links/runs.
-   [ ] Window runs/closes normally.
-   [ ] Sound plays and exits normally.
-   [ ] Image extension works.
-   [ ] Debug starts.

## Debugger

-   [ ] Initial and live breakpoints work.
-   [ ] Continue / Over / Into / Out work.
-   [ ] Step Into reaches user code rather than Small/STL internals.
-   [ ] Locals, user globals, and String values display.
-   [ ] Learner console appears.
-   [ ] Program/window exit ends the session cleanly.

## Tutorial

-   [ ] Expected core + extension lessons appear.
-   [ ] All 88 Korean core lessons and three Image extension lessons load.
-   [ ] Available language selection and missing-translation fallback work.
-   [ ] Try This Code, exercises, and solutions work.
-   [ ] Relative images render.
-   [ ] Preview line numbers are not clipped.
-   [ ] Preview has no breakpoint/debug markers.

## Runtime

-   [ ] `SmallMain()` exits normally.
-   [ ] Sound cleanup does not crash.
-   [ ] Manual `main()` examples use InitializeSmall/ShutdownSmall.
-   [ ] IDE Run/Debug console pause works for SmallMain and manual main programs.
-   [ ] Runtime-only programs terminate without IDE pause support.

These are manual release checks, not completed validation claims. See
`SETUP_VALIDATION.md` for known baseline failures.

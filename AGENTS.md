# Small C++ development instructions

Read `docs/PHILOSOPHY.md` before changing product behavior. The existing source,
learner vocabulary, native Qt UI, runtime/IDE boundary, and extension model are
the baseline. Discuss major architecture changes with the user before implementing
them. Do not introduce a web UI or rename/reorganize the source tree incidentally.

For each change:

1. Check `git status --short --branch`, the current diff, and recent commits.
   Preserve unrelated user changes; do not reset, overwrite, or stage them.
2. Make the smallest coherent change. Keep product changes separate from build,
   documentation, and repository setup changes when they serve different purposes.
3. Build and run tests appropriate to the change, following `docs/DEVELOPMENT.md`.
   Record known baseline failures separately; never describe a failing suite as green.
4. Review `git diff`, `git diff --cached`, and `git diff --check` before committing.
5. Stage explicit paths and create meaningful commits describing the result.
   Use `fix:`, `feat:`, `docs:`, or `chore:` as appropriate. Do not amend history,
   force-push, merge, or publish changes unless the user authorizes that operation.

Build products, Qt kits, compiler bundles, personal settings, and secrets do not
belong in Git. Keep build output in `build/`. Commit tutorial images, resources,
examples, manifests, and shared build configuration. Existing historical validation
reports are retained as evidence, not claims about the current version.

The initial GitHub upload is authorized by the setup request. Subsequent feature
work should report changes, validation, and commit IDs before any requested push.

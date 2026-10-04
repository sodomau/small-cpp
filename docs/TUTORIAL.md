# Tutorial — Phase 4C (v0.27)

## What is included

The approved Curriculum v2 is preserved: six parts, 36 lesson titles, and file
I/O isolated in Part IV. **Only Lessons 1–5 have authored lesson content in this
release.** Each has two runnable teaching examples and exactly two exercises,
with a starter, one hint, and a complete solution for each exercise.

| Lesson | Exercise 1 | Exercise 2 |
| --- | --- | --- |
| 1. Hello, Small C++! | Print a name | Print a three-line introduction |
| 2. Variables and Values | Store and print age | Calculate a rectangle's area |
| 3. Input and Output | Read a name and greet | Read two numbers and add them |
| 4. Making Decisions — if | Print only for a positive value | Child / Teenager / Adult |
| 5. Repeating with for | Print 1 through 10 | Print one multiplication table |

Prose, hints, and exercise instructions are initially in **Korean**. Menu/button
names follow the existing English IDE, and the runnable code mostly uses short
English console messages. There is no multilingual course manager in this slice.

## Learner workflow

Choose **Learn → Tutorial...**. The browser is created on demand and is modeless:
the editor remains usable while the lesson window is open. The main editor has
no permanent learning sidebar.

The left side shows the curriculum. Lessons 6–36 say **준비 중**. Selecting one
explains that its content has not yet been written; it is not locked by a
prerequisite. Published lessons can be visited in any order.

The right side is a scrolling page: goal, motivation, complete source examples,
explanation, two exercises, and an optional related Reference example.

**Try This Code**, exercise **Try**, and **Try Solution** each create a new,
editable, unsaved tab. They never overwrite an existing tab and never execute
code automatically. The source is complete, including `void small_main()`.
Press the IDE's Run/F5 to compile it. Console input happens in the separate
program console, not Diagnostics.

Hint and Solution are collapsed initially. Their buttons reveal content inline.
There is no penalty, grading, telemetry, completion gate, badge, or account.
Showing an answer does not mark the exercise as solved.

**Next** (and **Finish** on Lesson 5) marks the current lesson as *read*. A check
mark means only that the reader pressed one of those buttons. It is not proof
of understanding or a passed exercise. Previous does not undo a read mark.
Last selected lesson and read marks are saved locally through QSettings.
The namespace is `tutorial/curriculumV2/`; only lesson IDs are persisted.

Code previews reuse CodeEditor/Highlighter. The selected IDE font (default
Consolas 14) and Light/Dark colors apply to previews and new tabs, including
solutions that are currently collapsed.

## Content layout

```text
tutorial/
├── catalog.json                 # Entire approved curriculum; only 5 source entries
├── 01_hello/
│   ├── lesson.json              # Goal, ordered text/code blocks, exactly 2 exercises
│   ├── intro.md
│   ├── explanation.md
│   ├── after.md
│   ├── example1.cpp
│   ├── example2.cpp
│   ├── exercise1_prompt.md
│   ├── exercise1_hint.md
│   ├── exercise1_starter.cpp
│   ├── exercise1_solution.cpp
│   └── exercise2_...            # Same four files
└── ...
```

Content is compiled into `ide/SmallTutorials.qrc`. It needs no WebEngine,
browser runtime, network access, or installed content directory. Markdown is
rendered through QTextDocument; code uses the existing C++ highlighter.
Supported prose is intentionally small: paragraphs, headings, emphasis, and
inline code. Executable code lives in separate `.cpp` files. Do not put fenced
code, raw HTML, external links or images in these initial lesson text files.

`TutorialCatalog` loads UTF-8 content, verifies identities/paths and the two-
exercise rule, and reports malformed built-in content instead of loading it
partially. `TutorialBrowser` handles reading and emits source-copy requests.
`MainWindow` alone creates editor tabs. No runtime or compiler change is needed.

## Authoring and verification

To edit a lesson, change its Markdown or C++ content and rebuild SmallCppIDE.
No widget code changes are needed for an existing lesson. Adding a lesson also
requires its catalog entry, qrc entries, and output fixtures. The initial
five-lesson count in `tools/verify_tutorial.py` is intentional for this release;
update that release expectation when the next slice is authored.

```text
python tools/verify_tutorial.py
python tools/verify_tutorial.py --compiler g++
python tools/verify_tutorial.py --compiler clang++
```

Without `--compiler`, validation checks catalog/resource identity and completeness.
With it, the script compiles all 30 source files and tests the expected emitted
console output against 50 fixtures. This does **not** run Qt: it extracts the
unchanged console routines verbatim from `small_runtime.cpp` for a console-only
harness. Input echo by Windows Terminal is not part of the expected C++ stdout.

For the actual Qt kit, configure `SMALL_BUILD_TESTS=ON` and build/run
`small_tutorial_ui_test`. Build the aggregate `small_tutorial_programs` target
to compile/link all lesson sources against the real prebuilt Small runtime.
These are separate checks; a successful source-only test is not a GUI result.

## Windows acceptance review

Keep a modified user tab open. From Tutorial, try Lesson 1's first example and
Lesson 3's first exercise. Verify that each becomes an independent dirty tab;
enter a name in the native console after Run. Reveal a hint and a solution,
then use Try Solution. Closing a copied tab must retain the existing save
confirmation behavior. Next/read marks should survive closing and reopening
the IDE. Also check Korean wrapping, code size and button reachability at the
actual Windows DPI/font size, in both Light and Dark.

After this slice, review wording, lesson length and layout before writing the
remaining 31 lessons. Examples remain separate lookup material, not lessons.

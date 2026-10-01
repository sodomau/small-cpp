# Folder projects

Choose **File → Open Project (Folder)…** to use a folder as a project, or **New Project…**
to create one with a starter `main.cpp`. No project configuration is required.
In the picker, enter the folder and choose **Open This Folder**. Files remain
visible for reference; selecting a file does not prevent opening the current folder.

The project name appears above the file tree, in the window title and in the
status bar. **Run Project**, **Debug Project** and **Publish Project** always
use the project, even when another file is selected. Files opened from elsewhere
have **[Outside Project]** on their tabs.

## Files and programs

All `.cpp` files in the folder and its subfolders compile together. Include
headers normally, for example `#include "logic/player.h"`. A project produces
one program and needs one `SmallMain()` or one ordinary `main()`. Additional
practice programs should be excluded or kept in another project folder.

Right-click the tree to create a source file or header, add existing files, or
choose **Exclude from Project**. Exclusion does not delete a file. Excluded
items remain visible in gray italic text and can be included again. The tree notices added and
removed files automatically. Run, Debug and Publish save modified project files
first; files outside the project are not saved or compiled by those actions.

Build folders (`build`, `CMakeFiles`, `.smallcpp`), version-control folders and
folders containing the `.smallcpp-package` export marker are ignored. Symbolic
links are not followed. Avoid putting program sources in these reserved folders.

Breakpoints and error navigation work across project source files and headers.
**Close Project** asks about modified project tabs, closes the project's tabs,
and keeps files opened from elsewhere. Cancelling keeps the project open.

## Resources and Publish

Run and Debug use the project folder as their working directory. Use relative
paths such as `data/message.txt` or `images/player.png` in your program.

Publish selects included images, sounds and other data automatically. You can
remove individual files from that export in the dialog. Subfolder paths are
preserved. Student source files, headers and relinking materials are not exported.
Share the entire exported folder. See [Publish](PUBLISH.md) for runtime files
and licenses. Export folders marked by Small C++ are excluded from later builds.

Third-party runtime DLLs must be supplied as project resources, along with any
required notices. The IDE does not discover their dependencies automatically.

## Optional settings

**File → Project Settings…** opens or creates `small.project` at the root.
This is a JSON file for exclusions and advanced compiler settings:

```json
{
  "version": 1,
  "name": "MyGame",
  "exclude": ["practice", "old.cpp"],
  "include_paths": ["vendor/include"],
  "library_paths": ["vendor/lib"],
  "libraries": ["example"],
  "compiler_options": ["-DEXAMPLE_FEATURE=1"],
  "linker_options": ["-Wl,--as-needed"]
}
```

Remove options you do not need. Paths are relative to the project folder unless
absolute. Exclusions name exact files or folders, including all descendants;
they are not wildcard patterns. A library can be a name resolved in
`library_paths`, or a path to an archive. Prefer relative paths when moving a
project between computers. Output filenames and compile-only options remain
controlled by the IDE.

Publish does not add resolved external library archives or a compiler setup.
Package licenses cover the bundled Small C++ and Qt components;
check the requirements of any additional library you choose.

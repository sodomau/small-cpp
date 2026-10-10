# MSYS2 environment

The MSYS2 integration keeps Small's existing editor and project rules. A folder
is a project; included `.cpp` files are compiled by GCC directly. CMake and Ninja
are available as external tools, but are not required for a student project.

## Open a terminal

Choose **Tools → MSYS2 Terminal**. The separate UCRT64 terminal starts in the
open project's root, or beside the current saved file. With no saved file or
project, it starts in `Documents/SmallCpp/Programs`.

The terminal and Small's Run/Debug use the same bundled environment:

```text
SmallCpp/
├─ SmallCppIDE.exe
└─ env/
   ├─ usr/bin/       # Bash, pacman, terminal
   └─ ucrt64/
      ├─ bin/       # GCC, GDB, Python and installed DLLs
      ├─ include/
      └─ lib/
```

The first terminal login initializes its own home and package keyring if needed.
The menu is disabled in a development build without the bundled terminal.

## Try a library

In the terminal:

```sh
pacman -S mingw-w64-ucrt-x86_64-fmt
```

A header-only example needs no `small.project`:

```cpp
#define FMT_HEADER_ONLY
#include <fmt/format.h>

void small_main()
{
    print(fmt::format("Hello, {}!", 42).c_str());
}
```

For a compiled library, remove `#define FMT_HEADER_ONLY` and provide the static
library path in `small.project`. Find the environment's path with
`cygpath -m /ucrt64/lib` and replace the example path below:

```json
{
    "libraries": ["C:/path/to/SmallCpp/env/ucrt64/lib/libfmt.a"]
}
```

Alternatively, use `library_paths` with `libraries: ["fmt"]`; Small currently
prefers `libfmt.a` when both static and import libraries exist. There is no
automatic package-to-linker configuration yet. GCC searches its own UCRT64
include directory, so `fmt` headers need no additional include path.

For dynamic linking, select `libfmt.dll.a` explicitly. Run finds the installed
`libfmt-12.dll` through the environment's PATH. For Publish, copy the DLL into
the project root so it is included as a resource beside the published EXE.
Other libraries may need additional dependent DLLs and their own license notices.
Small does not yet collect arbitrary external package DLL dependencies automatically.

## Environment maintenance

Use UCRT64 package names (`mingw-w64-ucrt-x86_64-...`) for native libraries.
Follow MSYS2's [package management](https://www.msys2.org/docs/package-management/)
and [full-system update](https://www.msys2.org/docs/updating/) procedures.
The compiler, Qt/KDE libraries and Small's prebuilt runtime need a compatible
kit. Toolchain upgrades require revalidation; see [development](DEVELOPMENT.md).

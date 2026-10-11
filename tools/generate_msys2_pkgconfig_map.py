#!/usr/bin/env python3

import json
import re
import subprocess
import sys
from collections import defaultdict


# Small C++ uses the MSYS2 UCRT64 environment.
PACKAGE_PREFIX = "mingw-w64-ucrt-x86_64-"

# pkg-config files belonging to UCRT64 packages.
# Examples:
#   ucrt64/lib/pkgconfig/fftw3.pc
#   ucrt64/share/pkgconfig/xxx.pc
PC_PATH_RE = re.compile(
    r"^ucrt64/(?:lib|share)/pkgconfig/(.+)\.pc$"
)


def update_file_database():
    """
    Update pacman's file database.

    All pacman output is redirected to stderr so that stdout can contain
    only the generated JSON.
    """
    print("Updating pacman file database...", file=sys.stderr)

    result = subprocess.run(
        ["pacman", "-Fy"],
        stdout=sys.stderr,
        stderr=sys.stderr,
    )

    if result.returncode != 0:
        raise RuntimeError("pacman -Fy failed")


def get_pkgconfig_files():
    """
    Scan the MSYS2 repository file database and find UCRT64 packages
    providing pkg-config (.pc) files.

    Returns:
        dict:
            pkg-config module name -> set of pacman package names
    """

    print("Scanning MSYS2 package database...", file=sys.stderr)

    mapping = defaultdict(set)

    # Stream the output instead of loading the entire output of
    # `pacman -Fl` into memory.
    process = subprocess.Popen(
        ["pacman", "-Fl"],
        stdout=subprocess.PIPE,
        stderr=sys.stderr,
        text=True,
        encoding="utf-8",
        errors="replace",
    )

    assert process.stdout is not None

    for line in process.stdout:
        line = line.rstrip()

        # Typical output:
        #
        # mingw-w64-ucrt-x86_64-fftw ucrt64/include/fftw3.h
        # mingw-w64-ucrt-x86_64-fftw ucrt64/lib/pkgconfig/fftw3.pc

        parts = line.split(maxsplit=1)

        if len(parts) != 2:
            continue

        package, path = parts

        # Ignore MSYS, MINGW64, CLANG64, etc.
        if not package.startswith(PACKAGE_PREFIX):
            continue

        match = PC_PATH_RE.match(path)

        if not match:
            continue

        module = match.group(1)

        mapping[module].add(package)

    return_code = process.wait()

    if return_code != 0:
        raise RuntimeError("pacman -Fl failed")

    return mapping


def make_output(mapping):
    """
    Convert sets to JSON-friendly values.

    Normally a pkg-config module is provided by exactly one pacman
    package. If multiple packages provide the same module, keep all
    package names so that the ambiguity is visible.
    """

    result = {}

    for module in sorted(mapping):
        packages = sorted(mapping[module])

        if len(packages) == 1:
            result[module] = packages[0]
        else:
            result[module] = packages

    return result


def main():
    update_file_database()

    mapping = get_pkgconfig_files()
    result = make_output(mapping)

    print(
        f"Found {len(result)} pkg-config modules.",
        file=sys.stderr,
    )

    # stdout is reserved exclusively for JSON.
    json.dump(
        result,
        sys.stdout,
        indent=2,
        sort_keys=True,
        ensure_ascii=False,
    )

    print()


if __name__ == "__main__":
    main()

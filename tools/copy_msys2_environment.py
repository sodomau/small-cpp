#!/usr/bin/env python3
"""Copy an initialized MSYS2 environment without user data or caches."""
import argparse
import json
import re
from pathlib import Path
import shutil


MINIMAL_PACKAGES = ('base', 'msys2-runtime',
                    'mingw-w64-ucrt-x86_64-gcc', 'mingw-w64-ucrt-x86_64-gdb')


def package_fields(path):
    fields = {}
    key = None
    for line in path.read_text(encoding='utf-8').splitlines():
        if line.startswith('%') and line.endswith('%'):
            key = line.strip('%')
            fields[key] = []
        elif line and key:
            fields[key].append(line)
    return fields


def minimal_package_files(source):
    packages, providers, owners = {}, {}, {}
    database = source / 'var/lib/pacman/local'
    for folder in database.iterdir():
        if not folder.is_dir():
            continue
        data = package_fields(folder / 'desc')
        data['FILES'] = package_fields(folder / 'files').get('FILES', [])
        name = data['NAME'][0]
        packages[name] = (folder.name, data)
        for provided in data.get('PROVIDES', []):
            providers[re.split('[<>=]', provided)[0]] = name
        for path in data['FILES']:
            if not path.endswith('/'):
                owners[path] = name
    selected = set()

    def include(dependency):
        name = re.split('[<>=]', dependency)[0]
        if name not in packages:
            name = providers.get(name, name)
        if name in selected:
            return
        if name not in packages:
            raise ValueError(f'Missing installed dependency: {dependency}')
        selected.add(name)
        for item in packages[name][1].get('DEPENDS', []):
            include(item)

    for name in MINIMAL_PACKAGES:
        include(name)
    directories = {path for name in selected for path in packages[name][1]['FILES']
                   if path.endswith('/')}
    return selected, owners, {packages[name][0] for name in selected}, directories


def copy_environment(source, destination, minimal=False):
    source = source.resolve()
    destination = destination.resolve()
    build = Path(__file__).resolve().parents[1] / 'build'
    if not destination.is_relative_to(build.resolve()):
        raise ValueError('Destination must be under build/.')
    if destination.exists() or destination.is_relative_to(source):
        raise ValueError('Use a fresh destination outside the source environment.')
    for name in ('usr/bin/bash.exe', 'usr/bin/pacman.exe',
                 'ucrt64/bin/g++.exe', 'ucrt64/bin/gdb.exe', 'msys2_shell.cmd'):
        if not (source / name).is_file():
            raise ValueError(f'Missing MSYS2 component: {name}')

    # Preserve package databases/configuration so pacman owns the copied tools.
    # Personal homes, generated keys, logs and caches must never be distributed.
    omitted = {'home', 'tmp', 'dev', 'var/cache', 'var/log', 'var/tmp',
               'etc/pacman.d/gnupg', 'etc/ssh', 'etc/passwd', 'etc/group',
               'etc/machine-id', 'var/lib/pacman/db.lck'}

    selected, owners, database_folders, directories = (
        minimal_package_files(source) if minimal else (set(), {}, set(), set()))

    def ignore(directory, names):
        relative = Path(directory).relative_to(source)
        excluded = []
        for name in names:
            path = (relative / name).as_posix()
            if (path in omitted or (Path(directory) / name).is_symlink()
                    or (minimal and path in owners and owners[path] not in selected)
                    or (minimal and relative.as_posix() == 'var/lib/pacman/local'
                        and (Path(directory) / name).is_dir() and name not in database_folders)):
                excluded.append(name)
        return excluded

    shutil.copytree(source, destination, ignore=ignore)
    # Cache/log contents stay private, but package-owned empty directories are
    # still part of the filesystem package and must pass pacman -Qk.
    for relative in directories:
        path = (destination / relative).resolve()
        if not path.is_relative_to(destination):
            raise ValueError(f'Invalid package directory: {relative}')
        path.mkdir(parents=True, exist_ok=True)
    for folder in ('home', 'tmp', 'dev', 'var/cache/pacman/pkg', 'var/log', 'var/tmp'):
        (destination / folder).mkdir(parents=True, exist_ok=True)
    packages = sorted(p.name for p in (destination / 'var/lib/pacman/local').iterdir()
                      if p.is_dir())
    (destination / 'smallcpp-environment.json').write_text(
        json.dumps({'environment': 'UCRT64', 'profile': 'minimal' if minimal else 'full',
                    'packages': packages}, indent=2) + '\n',
        encoding='utf-8')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source', type=Path, required=True)
    parser.add_argument('--destination', type=Path, required=True)
    parser.add_argument('--minimal', action='store_true',
                        help='Keep base, GCC, GDB and their installed dependencies.')
    args = parser.parse_args()
    copy_environment(args.source, args.destination, minimal=args.minimal)
    print(args.destination)

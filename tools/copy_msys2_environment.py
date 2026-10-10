#!/usr/bin/env python3
"""Copy an initialized MSYS2 environment without user data or caches."""
import argparse
import json
from pathlib import Path
import shutil


def copy_environment(source, destination):
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

    def ignore(directory, names):
        relative = Path(directory).relative_to(source)
        return [name for name in names
                if (relative / name).as_posix() in omitted
                or (Path(directory) / name).is_symlink()]

    shutil.copytree(source, destination, ignore=ignore)
    for folder in ('home', 'tmp', 'dev', 'var/cache/pacman/pkg', 'var/log', 'var/tmp'):
        (destination / folder).mkdir(parents=True, exist_ok=True)
    packages = sorted(p.name for p in (destination / 'var/lib/pacman/local').iterdir()
                      if p.is_dir())
    (destination / 'smallcpp-environment.json').write_text(
        json.dumps({'environment': 'UCRT64', 'packages': packages}, indent=2) + '\n',
        encoding='utf-8')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source', type=Path, required=True)
    parser.add_argument('--destination', type=Path, required=True)
    args = parser.parse_args()
    copy_environment(args.source, args.destination)
    print(args.destination)

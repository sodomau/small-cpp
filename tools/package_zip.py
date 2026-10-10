#!/usr/bin/env python3
"""Create a portable ZIP, preserving directories needed on first MSYS2 login."""
import argparse
from pathlib import Path
import zipfile


def package_zip(package, output):
    package = package.resolve()
    output = output.resolve()
    build = Path(__file__).resolve().parents[1] / 'build'
    if not package.is_dir():
        raise ValueError('Package directory does not exist.')
    if not output.is_relative_to(build.resolve()) or output.is_relative_to(package):
        raise ValueError('ZIP output must be under build/, outside the package.')
    if output.exists():
        raise ValueError('Use a fresh ZIP destination to preserve previous artifacts.')
    output.parent.mkdir(parents=True, exist_ok=True)
    with zipfile.ZipFile(output, 'x', compression=zipfile.ZIP_DEFLATED,
                         compresslevel=6, allowZip64=True) as archive:
        for path in package.rglob('*'):
            if path.is_symlink():
                raise ValueError(f'Symlinks must be resolved before packaging: {path}')
            # Writing directories explicitly preserves empty tmp/dev/cache paths.
            archive.write(path, path.relative_to(package).as_posix())
    with zipfile.ZipFile(output) as archive:
        bad = archive.testzip()
        if bad:
            raise ValueError(f'ZIP integrity check failed: {bad}')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--package', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    package_zip(args.package, args.output)
    print(f'Verified ZIP: {args.output} ({args.output.stat().st_size} bytes)')

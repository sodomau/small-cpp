"""Assemble notices from the exact source archives and installed Qt SBOMs.

Run after downloading and checking the source inventory. No network access.
The source archives themselves must be published alongside the binary archive.
"""
import argparse
import hashlib
import json
from pathlib import Path, PurePosixPath
import re
import shutil
import tarfile


def prepare(sources: Path, qt: Path, compiler: Path, output: Path):
    if output.exists():
        raise ValueError('Use a fresh output directory')
    archives = sorted(p for p in sources.iterdir() if p.is_file() and
                      p.name.endswith(('.tar.gz', '.tar.xz', '.tar.bz2')) and
                      p.name != 'mingw-builds-5.0.0.tar.gz')
    required = ['qtbase-everywhere-src-6.11.2.tar.xz',
                'qtmultimedia-everywhere-src-6.11.2.tar.xz',
                'qtsvg-everywhere-src-6.11.2.tar.xz', 'gcc-13.1.0.tar.xz',
                'binutils-2.39.tar.xz', 'gdb-11.2.tar.xz',
                'mingw-builds-20230524.tar.gz',
                '12d1cb5b7c60901e36163b3e0599f11703c4946a.tar.gz',
                'c3e587c067a00a561899d49d3e63a659e38802ec.tar.gz',
                'bzip2-1.0.6.tar.gz', 'expat-2.5.0.tar.xz', 'gdbm-1.19.tar.gz',
                'gmp-6.2.1.tar.xz', 'isl-0.25.tar.xz', 'libffi-3.2.1.tar.gz',
                'libgnurx-2.8.0.tar.xz', 'libiconv-1.17.tar.gz', 'make-4.2.1.tar.bz2',
                'mpc-1.2.1.tar.gz', 'mpfr-4.1.0.tar.xz', 'ncurses-6.2.tar.gz',
                'OpenSSL_1_1_1k.tar.gz', 'readline-8.1.tar.gz',
                'sqlite-autoconf-3350500.tar.gz', 'tcl8.6.11-src.tar.gz',
                'termcap-1.3.1.tar.gz', 'tk8.6.11-src.tar.gz', 'v1.2.13.tar.gz',
                'xz-5.2.5.tar.gz']
    for name in required:
        if not (sources / name).is_file():
            raise ValueError('Missing source archive: ' + name)
    output.mkdir(parents=True)
    inventory = []
    notice_pattern = re.compile(r'^(copying|copyright|licen[sc]e|notice|authors|patents)([.\-_].*)?$', re.I)
    for archive in archives:
        count = 0
        # Never execute source files or extract archive links.
        with tarfile.open(archive) as tree:
            for member in tree:
                path = PurePosixPath(member.name)
                if not member.isfile() or '..' in path.parts or path.is_absolute():
                    continue
                if (notice_pattern.match(path.name) or 'LICENSES' in path.parts or
                        path.name == 'qt_attribution.json'):
                    target = output / 'source-notices' / archive.name / Path(*path.parts)
                    target.parent.mkdir(parents=True, exist_ok=True)
                    with tree.extractfile(member) as source, target.open('wb') as destination:
                        shutil.copyfileobj(source, destination)
                    count += 1
        with archive.open('rb') as source:
            digest = hashlib.file_digest(source, 'sha256').hexdigest()
        inventory.append({'file': archive.name, 'bytes': archive.stat().st_size,
                          'sha256': digest,
                          'noticeFiles': count})
    shutil.copytree(compiler / 'licenses', output / 'toolchain')
    shutil.copyfile(compiler / 'build-info.txt', output / 'toolchain-build-info.txt')
    sbom_out = output / 'qt-sbom'
    sbom_out.mkdir()
    sections = ['Small C++ Windows portable package\n',
                'Small C++ uses Qt 6.11.2 dynamically linked libraries under LGPL-3.0.\n'
                'Qt copyright: The Qt Company Ltd. and other contributors.\n'
                'Qt Core, Gui, Widgets, Network, Multimedia and Svg are deployed.\n'
                'Qt includes third-party components with their own notices below.\n'
                'The optional FFmpeg, software OpenGL and system D3D compiler binaries are not shipped.\n'
                'No changes were made to the Qt or toolchain binaries.\n'
                'You may replace compatible Qt DLLs and debug/reverse engineer Small C++ for that purpose.\n'
                'See SOURCE_ACCESS.md for source archives and rebuild instructions.\n',
                'The compiler directory contains MinGW-W64 GCC 13.1.0 (POSIX/SEH/MSVCRT, rt_v11-rev1),\n'
                'binutils 2.39, GDB 11.2 and their dependencies.\n'
                'They retain GPL/LGPL/BSD and other respective terms, not Small C++ MIT terms.\n'
                'Their complete installed notice tree is in toolchain/.\n'
                'Exact recorded build configuration and patch names: toolchain-build-info.txt.\n'
                'Source archives include the upstream code, mingw-builds scripts and patches.\n']
    for module in ['qtbase', 'qtmultimedia', 'qtsvg']:
        path = qt / 'sbom' / (module + '-6.11.2.spdx.json')
        shutil.copyfile(path, sbom_out / path.name)
        data = json.loads(path.read_text(encoding='utf-8'))
        for package in data.get('packages', []):
            sections.append('\n' + package['name'] + '\n' +
                            package.get('copyrightText', '') + '\nLicense: ' +
                            package.get('licenseDeclared', 'See source notices') + '\n')
        for license_info in data.get('hasExtractedLicensingInfos', []):
            sections.append('\n' + license_info['licenseId'] + '\n' + license_info['extractedText'] + '\n')
        for config in qt.glob('config_' + module + '.*'):
            shutil.copyfile(config, sbom_out / config.name)
    (output / 'THIRD_PARTY.txt').write_text('\n'.join(sections), encoding='utf-8', newline='\n')
    (output / 'source-inventory.json').write_text(json.dumps(inventory, indent=2) + '\n', encoding='utf-8', newline='\n')
    print(f'{len(archives)} archives; {sum(item["noticeFiles"] for item in inventory)} notice files')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--sources', type=Path, required=True)
    parser.add_argument('--qt', type=Path, required=True)
    parser.add_argument('--compiler', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    prepare(args.sources, args.qt, args.compiler, args.output)

"""Collect exact Craft editor and matching MinGW toolchain sources/notices."""
import argparse
import hashlib
import json
from pathlib import Path, PurePosixPath
import re
import shutil
import tarfile
import zipfile


def prepare(craft, records, compiler, sources, output):
    if output.exists():
        raise ValueError('Use a fresh notices directory')
    output.mkdir(parents=True)
    shutil.copytree(compiler / 'licenses', output / 'toolchain')
    shutil.copy2(compiler / 'build-info.txt', output / 'toolchain-build-info.txt')
    inventory = []
    pattern = re.compile(r'^(copying|copyright|licen[sc]e|notice|authors|patents)([.\-_].*)?$', re.I)
    for package, version in records.items():
        if package in ('libs/runtime', 'dev-utils/mingw-w64'):
            continue
        folder = craft / 'download/archives' / package
        archives = [p for p in folder.iterdir() if p.name.endswith(('.tar.xz', '.tar.gz', '.tar.bz2', '.tgz', '.zip'))]
        if not archives:
            raise ValueError('Missing sources: ' + package)
        for archive in archives:
            destination = sources / package / archive.name
            destination.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(archive, destination)
    for archive in sources.rglob('*'):
        if not archive.is_file() or not archive.name.endswith(('.tar.xz', '.tar.gz', '.tar.bz2', '.tgz', '.zip')):
            continue
        relative = archive.relative_to(sources)
        count = 0
        def save(name, stream):
            nonlocal count
            path = PurePosixPath(name)
            if path.is_absolute() or '..' in path.parts:
                return
            if not (pattern.match(path.name) or 'LICENSES' in path.parts or path.name == 'qt_attribution.json'):
                return
            # Flatten long upstream paths so the Windows package stays usable.
            archive_id = hashlib.sha256(relative.as_posix().encode()).hexdigest()[:12]
            notice_id = hashlib.sha256(name.encode()).hexdigest()[:16]
            target = output / 'source-notices' / archive_id / (notice_id + '-' + path.name[:48])
            target.parent.mkdir(parents=True, exist_ok=True)
            with target.open('wb') as writer:
                shutil.copyfileobj(stream, writer)
            count += 1
        if archive.suffix == '.zip':
            with zipfile.ZipFile(archive) as tree:
                for item in tree.infolist():
                    if not item.is_dir():
                        with tree.open(item) as stream:
                            save(item.filename, stream)
        else:
            with tarfile.open(archive) as tree:
                for item in tree:
                    if item.isfile():
                        with tree.extractfile(item) as stream:
                            save(item.name, stream)
        with archive.open('rb') as stream:
            digest = hashlib.file_digest(stream, 'sha256').hexdigest()
        inventory.append({'file': relative.as_posix(), 'sha256': digest, 'noticeFiles': count})
    (output / 'source-inventory.json').write_text(json.dumps(inventory, indent=2) + '\n', encoding='utf-8')
    (output / 'editor-packages.json').write_text(json.dumps(records, indent=2) + '\n', encoding='utf-8')
    (output / 'THIRD_PARTY.txt').write_text(
        'Small C++ v0.76.14 Windows distribution\n\n'
        'Small C++ materials use MIT. Third-party materials retain their own licenses.\n'
        'The editor dynamically links Qt 6.11.1 and KDE Frameworks 6.30.0.\n'
        'Qt is used under LGPL-3.0. KDE files retain their individual LGPL/MIT/BSD terms.\n'
        'Full component notices and Qt third-party attributions are in source-notices/.\n'
        'Exact installed Craft package versions are in editor-packages.json.\n'
        'The editor uses GCC 14.2 runtime DLLs and MinGW-w64 v12 winpthreads.\n'
        'The learner compiler is MinGW GCC 14.2.0, with its original complete\n'
        'notices and build record in toolchain/ and toolchain-build-info.txt.\n'
        'All third-party binaries are unmodified. Compatible DLL replacement and\n'
        'debugging/reverse engineering for that purpose are permitted.\n'
        'See SOURCE_ACCESS.md for corresponding source archives and rebuild inputs.\n', encoding='utf-8')
    (output / 'SOURCE_ACCESS.md').write_text(
        '# Corresponding source and rebuild inputs\n\n'
        'Download `SmallCpp-v0.76.14-ThirdPartySources.zip` from\n'
        'https://github.com/sodomau/small-cpp/releases/tag/v0.76.14 .\n'
        'It contains the exact upstream Qt/KDE/dependency source archives,\n'
        'the Craft blueprint snapshot (including applied patches), GCC 14.2\n'
        'and MinGW-w64 sources, plus the compiler dependencies, exact recorded\n'
        'git inputs, build scripts and patches for the matching GCC 14.2 toolchain.\n'
        'The original build-info.txt records its build flags and patches.\n\n'
        'See source-inventory.json for SHA-256 checksums. Qt/KDE can be rebuilt\n'
        'using Craft and the package versions in editor-packages.json.\n'
        'Small C++ source and build guidance are at the v0.76.14 repository tag\n'
        'in docs/DEVELOPMENT.md. Build with the matching Qt/KDE MinGW kit.\n'
        'Runtime DLLs are dynamically linked and replaceable with compatible builds.\n', encoding='utf-8')
    print(f'{len(inventory)} source archives collected')


if __name__ == '__main__':
    p = argparse.ArgumentParser(description=__doc__)
    for name in ('craft', 'records', 'compiler', 'sources', 'output'):
        p.add_argument('--' + name, type=Path, required=True)
    a = p.parse_args()
    prepare(a.craft, json.loads(a.records.read_text()), a.compiler, a.sources, a.output)

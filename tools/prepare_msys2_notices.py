"""Collect exact MSYS2 source packages and installed notices for a release."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import hashlib
import io
import json
from pathlib import Path, PurePosixPath
import re
import shutil
import subprocess
import tarfile
import tempfile
import urllib.request
import zipfile

from copy_msys2_environment import minimal_package_files, package_fields


def collect_source_notices(environment, archive, listing, notices):
    pattern = re.compile(r'^(copying|copyright|licen[sc]e|notice|authors|patents)([.\-_].*)?$', re.I)
    count = 0
    index = []
    def save(name, content):
        nonlocal count
        path = PurePosixPath(name)
        if not (pattern.match(path.name) or 'LICENSES' in path.parts or path.name == 'qt_attribution.json'):
            return
        identity = hashlib.sha256((archive.name + '/' + name).encode()).hexdigest()[:24]
        target = notices / 'source-notices' / (identity + '-' + path.name[:48])
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_bytes(content)
        index.append({'source': archive.name, 'upstreamPath': name,
                      'notice': target.relative_to(notices).as_posix()})
        count += 1
    tar = environment / 'usr/bin/bsdtar.exe'
    for name in listing.splitlines():
        if name.endswith('/'):
            continue
        path = PurePosixPath(name)
        nested = name.endswith(('.tar.xz', '.tar.gz', '.tar.bz2', '.tgz', '.tar', '.tar.lz', '.zip'))
        if not (nested or pattern.match(path.name)):
            continue
        content = subprocess.run([str(tar), '-xOf', str(archive), name],
                                 capture_output=True, check=True).stdout
        if name.endswith('.zip'):
            with zipfile.ZipFile(io.BytesIO(content)) as upstream:
                for member in upstream.infolist():
                    if not member.is_dir() and pattern.match(PurePosixPath(member.filename).name):
                        save(name + '/' + member.filename, upstream.read(member))
        elif name.endswith('.tar.lz'):
            with tempfile.TemporaryDirectory(dir=notices) as folder:
                upstream = Path(folder) / 'upstream.tar.lz'
                upstream.write_bytes(content)
                members = subprocess.check_output([str(tar), '-tf', str(upstream)], text=True)
                for member in members.splitlines():
                    if not member.endswith('/') and pattern.match(PurePosixPath(member).name):
                        text = subprocess.check_output([str(tar), '-xOf', str(upstream), member])
                        save(name + '/' + member, text)
        elif nested:
            with tarfile.open(fileobj=io.BytesIO(content), mode='r:*') as upstream:
                for member in upstream:
                    if member.isfile() and (pattern.match(PurePosixPath(member.name).name)
                            or 'LICENSES' in PurePosixPath(member.name).parts
                            or PurePosixPath(member.name).name == 'qt_attribution.json'):
                        save(name + '/' + member.name, upstream.extractfile(member).read())
        else:
            save(name, content)
    directory = notices / 'source-notice-index'
    directory.mkdir(parents=True, exist_ok=True)
    (directory / (archive.name + '.json')).write_text(json.dumps(index, indent=2) + '\n', encoding='utf-8')
    return count


def prepare(environment, package, sources, notices, version):
    root = Path(__file__).resolve().parents[1] / 'build'
    for path in (sources, notices):
        if not path.resolve().is_relative_to(root.resolve()):
            raise ValueError('Generated sources and notices must stay under build/.')
    selected, owners, _, _ = minimal_package_files(environment)
    # Include package owners of the deployed editor/runtime and learner import libs.
    for path in package.rglob('*'):
        if not path.is_file() or path.is_relative_to(package / 'env'):
            continue
        relative = path.relative_to(package).as_posix()
        candidates = ['ucrt64/' + relative, 'ucrt64/bin/' + relative,
                      'ucrt64/share/qt6/' + relative,
                      'ucrt64/lib/' + path.name]
        for candidate in candidates:
            if candidate in owners:
                selected.add(owners[candidate])
    records = []
    for folder in (environment / 'var/lib/pacman/local').iterdir():
        if not folder.is_dir():
            continue
        fields = package_fields(folder / 'desc')
        if fields['NAME'][0] in selected:
            records.append(fields)
    sources.mkdir(parents=True, exist_ok=True)
    notices.mkdir(parents=True, exist_ok=True)
    archives = {}
    for fields in records:
        base = fields.get('BASE', fields['NAME'])[0]
        release = fields['VERSION'][0].split(':')[-1]
        repository = 'mingw' if base.startswith('mingw-w64-') else 'msys'
        name = f'{base}-{release}.src.tar.zst'
        archives[name] = f'https://repo.msys2.org/{repository}/sources/{name}'
    def collect(item):
        name, url = item
        path = sources / name
        if not path.exists():
            temporary = path.with_suffix('.download')
            with urllib.request.urlopen(url, timeout=120) as response, temporary.open('wb') as target:
                shutil.copyfileobj(response, target)
            temporary.replace(path)
        # A source-only package must include its recipe, not an HTML error page.
        listing = subprocess.run([str(environment / 'usr/bin/bsdtar.exe'), '-tf', str(path)],
                                 capture_output=True, text=True, check=True).stdout
        if 'PKGBUILD' not in listing:
            raise ValueError(f'Source recipe missing: {name}')
        with path.open('rb') as stream:
            digest = hashlib.file_digest(stream, 'sha256').hexdigest()
        print(f'Collected {name}', flush=True)
        count = collect_source_notices(environment, path, listing, notices)
        return {'file': name, 'url': url, 'sha256': digest, 'noticeFiles': count}
    with ThreadPoolExecutor(max_workers=4) as pool:
        inventory = list(pool.map(collect, sorted(archives.items())))
    # Preserve the package-provided license/attribution files and common texts.
    for relative, owner in owners.items():
        if owner not in selected or '/licenses/' not in '/' + relative:
            continue
        source = environment / relative
        target = notices / 'package-notices' / relative
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(source, target)
    manifest = [{'name': f['NAME'][0], 'version': f['VERSION'][0],
                 'base': f.get('BASE', f['NAME'])[0], 'licenses': f.get('LICENSE', [])}
                for f in sorted(records, key=lambda f: f['NAME'][0])]
    for target in (sources, notices):
        (target / 'source-inventory.json').write_text(json.dumps(inventory, indent=2) + '\n', encoding='utf-8')
        (target / 'packages.json').write_text(json.dumps(manifest, indent=2) + '\n', encoding='utf-8')
    (notices / 'THIRD_PARTY.txt').write_text(
        f'Small C++ v{version} Windows distribution\n\n'
        'Small C++ materials use MIT. Third-party components retain their own licenses.\n'
        'The IDE dynamically links MSYS2 UCRT64 Qt and KDE Frameworks.\n'
        'The learner environment includes MSYS2, GCC, GDB and their dependencies.\n'
        'Exact versions and license declarations are recorded in packages.json.\n'
        'Package-provided notices are preserved in package-notices/; upstream license,\n'
        'copyright and attribution files are collected in source-notices/.\n'
        'source-notice-index/ maps those files back to their original archives and paths.\n'
        'Complete original source packages include license texts, build recipes and patches.\n'
        'Compatible DLL replacement and reverse engineering for that purpose are permitted.\n'
        'See SOURCE_ACCESS.md for corresponding sources and rebuild instructions.\n', encoding='utf-8')
    access = (f'# Corresponding sources — v{version}\n\n'
        f'Download SmallCpp-v{version}-ThirdPartySources.zip from\n'
        f'https://github.com/sodomau/small-cpp/releases/tag/v{version}.\n\n'
        'It contains the exact MSYS2 source-only packages for the distributed components,\n'
        'including upstream source archives, PKGBUILD recipes and patches.\n'
        'SHA-256 checksums and original URLs are in source-inventory.json.\n'
        'Extract each source package with bsdtar; inspect its PKGBUILD and build it\n'
        'in the matching MSYS2/MSYSTEM environment with makepkg or makepkg-mingw.\n'
        'See https://www.msys2.org/wiki/Creating-Packages/ for build guidance.\n'
        f'Small C++ itself is available at the v{version} repository tag;\n'
        'its build instructions are in docs/DEVELOPMENT.md.\n')
    for target in (sources, notices):
        (target / 'SOURCE_ACCESS.md').write_text(access, encoding='utf-8')
    print(f'{len(manifest)} binary packages; {len(inventory)} source packages', flush=True)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    for name in ('environment', 'package', 'sources', 'notices'):
        parser.add_argument('--' + name, type=Path, required=True)
    parser.add_argument('--version', required=True)
    args = parser.parse_args()
    prepare(args.environment, args.package, args.sources, args.notices, args.version)

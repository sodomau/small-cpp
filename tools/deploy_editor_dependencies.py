"""Copy the recursive PE DLL imports not handled by windeployqt."""
import argparse
import json
from pathlib import Path
import re
import shutil
import subprocess


def deploy(package, prefix, objdump):
    queue = list(package.rglob('*.dll')) + [package / 'SmallCppIDE.exe']
    seen = set()
    copied = []
    while queue:
        binary = queue.pop()
        if binary in seen:
            continue
        seen.add(binary)
        result = subprocess.run([str(objdump), '-p', str(binary)],
                                capture_output=True, text=True, check=True)
        for name in re.findall(r'DLL Name:\s*(\S+)', result.stdout):
            source = next((folder / name for folder in
                           (prefix / 'bin', prefix / 'mingw64/bin')
                           if (folder / name).is_file()), None)
            if source is None:  # Windows system imports stay with Windows.
                continue
            target = package / name
            if not target.exists():
                shutil.copy2(source, target)
                copied.append(name)
            queue.append(target)
    (package / 'editor-dependencies.json').write_text(
        json.dumps(sorted(copied), indent=2) + '\n', encoding='utf-8')
    (package / 'qt.conf').write_text('[Paths]\nPrefix=.\nPlugins=.\nData=.\n', encoding='ascii')
    # Keep popup/menu resources app-local as well as the syntax resources in DLLs.
    for relative in ('share/katepart6', 'share/kf6/ktexteditor', 'share/kxmlgui6'):
        source = prefix / relative
        if source.is_dir():
            shutil.copytree(source, package / relative, dirs_exist_ok=True)
    print(f'Collected {len(copied)} additional editor DLLs')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--package', type=Path, required=True)
    parser.add_argument('--prefix', type=Path, required=True)
    parser.add_argument('--objdump', type=Path, required=True)
    args = parser.parse_args()
    deploy(args.package, args.prefix, args.objdump)

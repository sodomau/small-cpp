"""Check that environment packaging preserves pacman without copying user data."""
from pathlib import Path
import io
import json
import sys
import tarfile
import tempfile
import unittest
import zipfile
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from copy_msys2_environment import copy_environment, RUNTIME_DIRECTORIES
from package_zip import package_zip
from prepare_msys2_notices import collect_source_notices, prepare


class EnvironmentPackagingTests(unittest.TestCase):
    def test_upstream_license_texts_are_preserved_without_extracting_source_paths(self):
        with tempfile.TemporaryDirectory(dir=ROOT / 'build') as folder:
            root = Path(folder)
            content = io.BytesIO()
            with tarfile.open(fileobj=content, mode='w:gz') as archive:
                for name, text in [('project/COPYING', b'license text'),
                                   ('project/LICENSES/MIT.txt', b'copyright text'),
                                   ('project/code.cpp', b'code')]:
                    info = tarfile.TarInfo(name)
                    info.size = len(text)
                    archive.addfile(info, io.BytesIO(text))
            with patch('prepare_msys2_notices.subprocess.run') as tar:
                tar.return_value.stdout = content.getvalue()
                count = collect_source_notices(root, root / 'source.src.tar.zst',
                    'package/upstream.tar.gz\n', root / 'notices')
            self.assertEqual(count, 2)
            files = list((root / 'notices/source-notices').iterdir())
            self.assertEqual({p.read_bytes() for p in files}, {b'license text', b'copyright text'})
            self.assertFalse((root / 'notices/project').exists())

    def test_sources_cover_deployed_editor_beyond_minimal_environment(self):
        with tempfile.TemporaryDirectory(dir=ROOT / 'build') as folder:
            root = Path(folder)
            environment, package = root / 'environment', root / 'package'
            entries = {
                'base': [], 'msys2-runtime': [],
                'mingw-w64-ucrt-x86_64-gcc': [],
                'mingw-w64-ucrt-x86_64-gdb': [],
                'editor': ['ucrt64/bin/editor.dll', 'ucrt64/share/licenses/editor/LICENSE'],
                'unused': ['ucrt64/bin/unused.dll'],
            }
            for name, files in entries.items():
                database = environment / 'var/lib/pacman/local' / name
                database.mkdir(parents=True)
                (database / 'desc').write_text(
                    f'%NAME%\n{name}\n\n%VERSION%\n1:2.3-4\n\n%LICENSE%\nMIT\n', encoding='utf-8')
                (database / 'files').write_text('%FILES%\n' + '\n'.join(files), encoding='utf-8')
                for relative in files:
                    path = environment / relative
                    path.parent.mkdir(parents=True, exist_ok=True)
                    path.write_bytes(b'fixture')
            package.mkdir()
            (package / 'editor.dll').write_bytes(b'fixture')
            with patch('prepare_msys2_notices.urllib.request.urlopen',
                       side_effect=lambda *args, **kwargs: io.BytesIO(b'source fixture')), \
                 patch('prepare_msys2_notices.subprocess.run') as tar:
                tar.return_value.stdout = 'editor/PKGBUILD\n'
                prepare(environment, package, root / 'sources', root / 'notices', '0.76.16')
            manifest = json.loads((root / 'notices/packages.json').read_text())
            self.assertIn('editor', [entry['name'] for entry in manifest])
            self.assertNotIn('unused', [entry['name'] for entry in manifest])
            self.assertTrue((root / 'sources/editor-2.3-4.src.tar.zst').is_file())
            self.assertEqual((root / 'notices/package-notices/ucrt64/share/licenses/editor/LICENSE').read_bytes(), b'fixture')

    def test_zip_extract_preserves_empty_first_login_directories(self):
        with tempfile.TemporaryDirectory(dir=ROOT / 'build') as folder:
            package = Path(folder) / 'portable'
            for relative in RUNTIME_DIRECTORIES:
                (package / 'env' / relative).mkdir(parents=True, exist_ok=True)
            (package / 'SmallCppIDE.exe').write_bytes(b'fixture')
            output = Path(folder) / 'portable.zip'
            package_zip(package, output)
            extracted = Path(folder) / 'extracted'
            with zipfile.ZipFile(output) as archive:
                archive.extractall(extracted)
            for relative in RUNTIME_DIRECTORIES:
                self.assertTrue((extracted / 'env' / relative).is_dir(), relative)
            self.assertEqual((extracted / 'SmallCppIDE.exe').read_bytes(), b'fixture')
            with self.assertRaises(ValueError):
                package_zip(package, output)
            with self.assertRaises(ValueError):
                package_zip(package, package / 'recursive.zip')

    def test_minimal_profile_keeps_dependencies_and_matching_database(self):
        with tempfile.TemporaryDirectory(dir=ROOT / 'build') as folder:
            source = Path(folder) / 'source'
            entries = {
                'base': (['shell>=1'], ['msys2_shell.cmd', 'var/cache/man/', 'var/log/old/']),
                'msys2-runtime': ([], ['usr/bin/msys-2.0.dll']),
                'bash': (['msys2-runtime'], ['usr/bin/bash.exe', 'usr/bin/pacman.exe']),
                'mingw-w64-ucrt-x86_64-gcc': (['shared-lib'], ['ucrt64/bin/g++.exe']),
                'mingw-w64-ucrt-x86_64-gdb': (['shared-lib'], ['ucrt64/bin/gdb.exe']),
                'shared-lib': ([], ['ucrt64/bin/shared.dll']),
                'qt-devel': (['shared-lib'], ['ucrt64/bin/Qt6Core.dll', 'ucrt64/include/qt.h']),
            }
            for name, (dependencies, files) in entries.items():
                database = source / 'var/lib/pacman/local' / (name + '-1')
                database.mkdir(parents=True)
                desc = '%NAME%\n' + name + '\n\n%DEPENDS%\n' + '\n'.join(dependencies)
                if name == 'bash':
                    desc += '\n\n%PROVIDES%\nshell=1\n'
                (database / 'desc').write_text(desc, encoding='utf-8')
                (database / 'files').write_text('%FILES%\n' + '\n'.join(files), encoding='utf-8')
                for file in files:
                    path = source / file
                    if file.endswith('/'):
                        path.mkdir(parents=True, exist_ok=True)
                        continue
                    path.parent.mkdir(parents=True, exist_ok=True)
                    path.write_text(file, encoding='utf-8')
            destination = Path(folder) / 'minimal'
            copy_environment(source, destination, minimal=True)
            self.assertTrue((destination / 'ucrt64/bin/shared.dll').is_file())
            self.assertFalse((destination / 'ucrt64/bin/Qt6Core.dll').exists())
            self.assertFalse((destination / 'ucrt64/include/qt.h').exists())
            self.assertTrue((destination / 'var/lib/pacman/local/bash-1/desc').is_file())
            self.assertFalse((destination / 'var/lib/pacman/local/qt-devel-1').exists())
            self.assertTrue((destination / 'var/cache/man').is_dir())
            self.assertTrue((destination / 'var/log/old').is_dir())
            # Resolve failures before creating a partial environment.
            (source / 'var/lib/pacman/local/base-1/desc').write_text(
                '%NAME%\nbase\n\n%DEPENDS%\nmissing-package\n', encoding='utf-8')
            with self.assertRaisesRegex(ValueError, 'Missing installed dependency'):
                copy_environment(source, Path(folder) / 'broken', minimal=True)
            self.assertFalse((Path(folder) / 'broken').exists())

    def test_package_database_survives_but_personal_data_does_not(self):
        (ROOT / 'build').mkdir(exist_ok=True)
        with tempfile.TemporaryDirectory(dir=ROOT / 'build') as folder:
            source = Path(folder) / 'source'
            public = ('usr/bin/bash.exe', 'usr/bin/pacman.exe',
                      'ucrt64/bin/g++.exe', 'ucrt64/bin/gdb.exe', 'msys2_shell.cmd',
                      'var/lib/pacman/local/gcc-test/desc', 'etc/pacman.conf')
            private = ('home/student/.ssh/id_ed25519', 'tmp/code.cpp',
                       'etc/pacman.d/gnupg/private-keys-v1.d/key',
                       'var/cache/pacman/pkg/download', 'var/log/pacman.log',
                       'var/lib/pacman/db.lck')
            for name in public + private:
                path = source / name
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text(name, encoding='utf-8')
            destination = Path(folder) / 'env'
            copy_environment(source, destination)
            for name in public:
                self.assertEqual((destination / name).read_bytes(), (source / name).read_bytes())
            for name in private:
                self.assertFalse((destination / name).exists(), name)
            with self.assertRaises(ValueError):
                copy_environment(source, destination)
            with self.assertRaises(ValueError):
                copy_environment(source, ROOT / 'outside-build-env')


if __name__ == '__main__':
    unittest.main()

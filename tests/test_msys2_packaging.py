"""Check that environment packaging preserves pacman without copying user data."""
from pathlib import Path
import sys
import tempfile
import unittest
import zipfile

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from copy_msys2_environment import copy_environment, RUNTIME_DIRECTORIES
from package_zip import package_zip


class EnvironmentPackagingTests(unittest.TestCase):
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

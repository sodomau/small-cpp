"""Check that environment packaging preserves pacman without copying user data."""
from pathlib import Path
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from copy_msys2_environment import copy_environment


class EnvironmentPackagingTests(unittest.TestCase):
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

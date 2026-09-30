#!/usr/bin/env python3
from pathlib import Path
root=Path(__file__).resolve().parents[1]
build=(root/"ide/BuildController.cpp").read_text(encoding="utf-8")
cmake=(root/"ide/CMakeLists.txt").read_text(encoding="utf-8")
ps=(root/"tools/package_release.ps1").read_text(encoding="utf-8")
assert 'compiler/bin/g++.exe' in build and 'QFileInfo::exists(bundled)' in build
assert 'packaging-info.txt' in cmake
assert 'windeployqt.exe' in ps and '--compiler-runtime' in ps
assert 'Copy-Item $exe' in ps
assert 'Copy-Item $runtime' in ps
assert 'Copy-Item $extensions' in ps
assert 'Get-ChildItem $build' not in ps
assert 'Copy-Item (Join-Path $build "*")' not in ps
assert 'OutputDir must not be inside BuildDir' in ps
assert '$toolchainRoot' in ps and 'g++.exe' in ps
print("Portable distribution recursion-safety check passed.")

bat=(root/"package_release.bat").read_text(encoding="utf-8")
assert "robocopy $toolchainRoot $compilerOut" in ps
assert "$robocopyExit -ge 8" in ps
assert "Release build not found" in ps
assert "More than one Release build was found" in ps
assert "package_release.ps1" in bat
assert "-ExecutionPolicy Bypass" in bat
print("One-click portable packaging checks passed.")

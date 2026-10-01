#!/usr/bin/env python3
from pathlib import Path
import json,re
root=Path(__file__).resolve().parents[1]
cm=(root/"ide/CMakeLists.txt").read_text(encoding="utf-8")
main=(root/"ide/main.cpp").read_text(encoding="utf-8")
tutorial=(root/"ide/TutorialBrowser.cpp").read_text(encoding="utf-8")
from tutorial_content import validate_pack
languages=json.loads((root/"tutorial/languages.json").read_text(encoding="utf-8"))
lessons, sources=validate_pack(root/"tutorial", languages["languages"], languages["default"])
assert len(lessons)==91
assert '"${SMALL_ROOT}/tutorial" "${SMALL_BIN}/tutorial"' in cm
assert 'SmallTutorials.qrc' not in cm
packager=(root/"tools/package_release.ps1").read_text(encoding="utf-8")
assert 'tutorial' in packager
assert 'SmallApp.qrc' in cm
assert 'smallcpp.rc' in cm and 'if(WIN32)' in cm
assert 'app.setWindowIcon(QIcon(":/small/app/smallcpp.png"))' in main
mainwindow=(root/"ide/MainWindow.cpp").read_text(encoding="utf-8")
assert 'new TutorialBrowser(tutorials_, nullptr)' in mainwindow
assert 'new ExamplesBrowser(examples_, nullptr)' in mainwindow
assert 'new TutorialBrowser(tutorials_, this)' not in mainwindow
assert 'new ExamplesBrowser(examples_, this)' not in mainwindow
assert (root/"ide/assets/smallcpp.ico").stat().st_size > 0
assert (root/"ide/assets/smallcpp.png").stat().st_size > 0
print("UI packaging, icon, modeless-window, and final tutorial publication checks passed.")

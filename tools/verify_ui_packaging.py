#!/usr/bin/env python3
from pathlib import Path
import json,re
root=Path(__file__).resolve().parents[1]
cm=(root/"ide/CMakeLists.txt").read_text()
main=(root/"ide/main.cpp").read_text()
tutorial=(root/"ide/TutorialBrowser.cpp").read_text()
qrc=(root/"ide/SmallTutorials.qrc").read_text()
catalog=json.loads((root/"tutorial/catalog.json").read_text())
assert 'SmallApp.qrc' in cm
assert 'smallcpp.rc' in cm and 'if(WIN32)' in cm
assert 'app.setWindowIcon(QIcon(":/small/app/smallcpp.png"))' in main
mainwindow=(root/"ide/MainWindow.cpp").read_text(encoding="utf-8")
assert 'new TutorialBrowser(tutorials_, nullptr)' in mainwindow
assert 'new ExamplesBrowser(examples_, nullptr)' in mainwindow
assert 'new TutorialBrowser(tutorials_, this)' not in mainwindow
assert 'new ExamplesBrowser(examples_, this)' not in mainwindow
for n in range(32,37):
    lesson=next(x for p in catalog["parts"] for x in p["lessons"] if x["number"]==n)
    assert lesson.get("source"), f"Lesson {n} is not published"
    assert f'alias="{lesson["source"]}"' in qrc, f"Lesson {n} manifest not embedded"
assert (root/"ide/assets/smallcpp.ico").stat().st_size > 0
assert (root/"ide/assets/smallcpp.png").stat().st_size > 0
print("UI packaging, icon, modeless-window, and final tutorial publication checks passed.")

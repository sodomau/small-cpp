#!/usr/bin/env python3
from pathlib import Path
root=Path(__file__).resolve().parents[1]
data=(root/"ide/ApiReference.cpp").read_text()
browser=(root/"ide/ApiBrowser.cpp").read_text()
main=(root/"ide/MainWindow.cpp").read_text()
required=["Print","InputInt","RandomInt","StopWatch","Sleep","String","Array","File.Open","RGB",
          "Window.Open","Window.FillCircle","Window.KeyDown","Window.MouseDown","PlaySound"]
for name in required: assert f'"{name}"' in data, name
assert "Extension — Image" in data and "DrawImage" in data
assert "Parameters" in browser and "Returns:" in browser and "Show C++ details" in browser
assert "API Reference..." in main and "browseApi" in main
print("Learner-friendly API reference coverage checks passed.")

# API notation must use types, while concrete variable names belong only in examples.
for usage in ["StopWatch.Elapsed()", "Timer.Start(interval, function)", "String.Length()",
              "Array.Length()", "File.Open(filename, mode)", "Window.FillCircle(x, y, radius, color)",
              "LoadImage(filename)"]:
    assert f'"{usage}"' in data, usage
for bad in ['"watch.Elapsed()"','"timer.Start(interval, function)"','"text.Length()"',
            '"values.Length()"','"file.Open(filename, mode)"','"window.FillCircle(x, y, radius, color)"',
            '"Image.Load(filename)"']:
    assert bad not in data, bad
assert "typeNodes" in browser and "memberName" in browser
cmake=(root/"ide/CMakeLists.txt").read_text()
import re
m=re.search(r"set\(SMALL_IDE_SOURCES\s+(.*?)\n\)", cmake, re.S)
assert m
missing=[x for x in m.group(1).split() if not (root/"ide"/x).exists()]
assert not missing, "CMake source files missing: "+", ".join(missing)
print("Canonical type.member API notation and source-list checks passed.")

assert "typeEntries" in browser
assert "hasMembers" in browser
assert "setSectionResizeMode(1, QHeaderView::ResizeToContents)" in browser
assert "splitter->setSizes({280, 720})" in browser
print("Selectable non-duplicated type nodes and API layout checks passed.")

for api in ["File.Input","File.InputInt","File.InputReal","File.Write","File.Print",
            "File.ReadInt","File.ReadReal","File.WriteInt","File.WriteReal",
            "Window.Width","Window.Height","Window.MouseX","Window.MouseY",
            "Image.Width","Image.Height"]:
    assert f'"{api}"' in data, api
for grouped in ["File.Input / InputInt / InputReal","File.Print / Write","binary numbers",
                "Window.Width / Height","Window.MouseX / MouseY","Image.Width / Height"]:
    assert f'"{grouped}"' not in data, grouped
print("One-API-one-entry checks passed.")

#!/usr/bin/env python3
from pathlib import Path
root=Path(__file__).resolve().parents[1]
data=(root/"ide/ApiReference.cpp").read_text(encoding="utf-8")
browser=(root/"ide/ApiBrowser.cpp").read_text(encoding="utf-8")
main=(root/"ide/MainWindow.cpp").read_text(encoding="utf-8")
required=["print","input_int","random_int","StopWatch","sleep","String","Array","File.open","rgb",
          "Window.open","Window.fill_circle","Window.key_down","Window.mouse_down","play_sound"]
for name in required: assert f'"{name}"' in data, name
assert "Extension — Image" in data and "draw_image" in data
assert "Parameters" in browser and "Returns:" in browser and "Show C++ details" in browser
assert "API Reference..." in main and "browseApi" in main
print("Learner-friendly API reference coverage checks passed.")

# API notation must use types, while concrete variable names belong only in examples.
for usage in ["StopWatch.elapsed()", "Timer.start(interval, function)", "String.length()",
              "Array.length()", "File.open(filename, mode)", "Window.fill_circle(x, y, radius, color)",
              "load_image(filename)"]:
    assert f'"{usage}"' in data, usage
for bad in ['"watch.elapsed()"','"timer.start(interval, function)"','"text.length()"',
            '"values.length()"','"file.open(filename, mode)"','"window.fill_circle(x, y, radius, color)"',
            '"Image.Load(filename)"']:
    assert bad not in data, bad
assert "typeNodes" in browser and "memberName" in browser
cmake=(root/"ide/CMakeLists.txt").read_text(encoding="utf-8")
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

for api in ["File.input","File.input_int","File.input_real","File.write","File.print",
            "File.read_int","File.read_real","File.write_int","File.write_real",
            "Window.width","Window.height","Window.mouse_x","Window.mouse_y",
            "Image.width","Image.height"]:
    assert f'"{api}"' in data, api
for grouped in ["File.input / input_int / input_real","File.print / write","binary numbers",
                "Window.width / height","Window.mouse_x / mouse_y","Image.width / height"]:
    assert f'"{grouped}"' not in data, grouped
print("One-API-one-entry checks passed.")

#!/usr/bin/env python3
from pathlib import Path
root=Path(__file__).resolve().parents[1]
h=(root/"extensions/image/include/small/image.h").read_text(encoding="utf-8")
impl=(root/"extensions/image/src/image.cpp").read_text(encoding="utf-8")
api=(root/"ide/ApiReference.cpp").read_text(encoding="utf-8")
for old in ["    Image();", "    explicit Image(const String& filename);", "void Load(", "void Save(", "IsEmpty"]:
    assert old not in h, old
for required in ["Image(int width, int height, Color fill = Black);",
                 "Image LoadImage(const String& filename);",
                 "void SaveImage(const Image& image, const String& filename);",
                 "void DrawImage("]:
    assert required in h, required
assert '"LoadImage"' in api and '"SaveImage"' in api
for old in ['"Image from file"','"Image.Load"','"Image.Save"','"Image.IsEmpty"']:
    assert old not in api, old
for p in (root/"extensions/image").rglob("*.cpp"):
    text=p.read_text(encoding="utf-8")
    assert ".Load(" not in text and ".Save(" not in text
print("Image value-object/free-function API design checks passed.")

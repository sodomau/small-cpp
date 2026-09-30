#!/usr/bin/env python3
from pathlib import Path
import json
root=Path(__file__).resolve().parents[1]
base=root/"extensions/image"
manifest=json.loads((base/"extension.json").read_text())
assert manifest["header"]=="small/image.h"
assert (base/"include/small/image.h").exists()
assert (base/"src/image.cpp").exists()
assert (base/"examples").is_dir()
assert (base/"tutorial").is_dir()
core=(root/"runtime/small.h").read_text()
assert "class Image" not in core and "DrawImage" not in core
registry=(root/"ide/ExtensionRegistry.cpp").read_text()
assert "extension.json" in registry and "QJsonDocument" in registry
build=(root/"ide/BuildController.cpp").read_text()
assert "ExtensionRegistry::discover" in build
assert "extension.includeDirectory" in build
assert "extension.libraryPath" in build
assert 'extension.id == "image"' not in build
cmake=(root/"ide/CMakeLists.txt").read_text()
assert "extensions/image/include/small/image.h" in cmake
assert "${SMALL_BIN}/extensions/image/lib/$<TARGET_FILE_NAME:small_image>" in cmake
print("Self-contained manifest-driven extension checks passed.")

# Image completeness content checks
assert (base/"examples/catalog.json").exists()
assert (base/"tutorial/catalog.json").exists()
examples=json.loads((base/"examples/catalog.json").read_text())
tutorial=json.loads((base/"tutorial/catalog.json").read_text())
assert len(examples["examples"]) >= 3
assert len(tutorial["lessons"]) >= 3
internal=(root/"runtime/small_internal.h").read_text()
runtime=(root/"runtime/small_runtime.cpp").read_text()
imagecpp=(base/"src/image.cpp").read_text()
assert "BlitRgba" in internal and "BlitRgba" in runtime and "BlitRgba" in imagecpp
assert "window.SetPixel" not in imagecpp
print("Image completeness content checks passed.")

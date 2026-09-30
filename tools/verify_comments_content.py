#!/usr/bin/env python3
from pathlib import Path
import json
root=Path(__file__).resolve().parents[1]
lesson=(root/"tutorial/02_lines/ko.md").read_text(encoding="utf-8")
assert "주석" in lesson and "`//`" in lesson
reference=(root/"examples/reference/comments.cpp").read_text(encoding="utf-8")
assert "//" in reference and "/*" in reference and "*/" in reference
catalog=json.loads((root/"examples/catalog.json").read_text(encoding="utf-8"))
assert any(e["id"]=="reference/comments" for e in catalog["examples"])
programs=list((root/"examples/programs").glob("*.cpp"))
assert all("//" in p.read_text(encoding="utf-8") for p in programs)
print(f"Comment teaching and example checks passed: {len(programs)} program examples.")

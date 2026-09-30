#!/usr/bin/env python3
from pathlib import Path
import json
root=Path(__file__).resolve().parents[1]
assert "comment(주석)" in (root/"tutorial/01_hello/after.md").read_text()
assert "`/*`" in (root/"tutorial/07_functions/after.md").read_text()
catalog=json.loads((root/"examples/catalog.json").read_text())
assert any(e["id"]=="reference/comments" for e in catalog["examples"])
programs=list((root/"examples/programs").glob("*.cpp"))
assert all("//" in p.read_text() for p in programs)
print(f"Comment teaching and example checks passed: {len(programs)} program examples.")

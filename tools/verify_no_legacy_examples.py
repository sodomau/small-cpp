#!/usr/bin/env python3
from pathlib import Path
root=Path(__file__).resolve().parents[1]
stray=sorted(p.name for p in (root/"examples").glob("*.cpp"))
if stray:
    raise SystemExit("Legacy top-level example files found: "+", ".join(stray))
print("No legacy top-level example .cpp files remain.")

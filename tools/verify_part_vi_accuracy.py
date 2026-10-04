#!/usr/bin/env python3
from pathlib import Path
root=Path(__file__).resolve().parents[1]
tutorial=root/"tutorial"
part6="\n".join(p.read_text(encoding="utf-8") for p in tutorial.glob("*/ko.md")
                 if "part: cpp\n" in p.read_text(encoding="utf-8"))
header=(root/"runtime/small.h").read_text(encoding="utf-8")
if "No Resize/Append operations." not in header:
    raise SystemExit("Expected Small Array fixed-size contract changed; review Part VI.")
for phrase in ["Add가 push_back으로", "Array.Add", "numbers.Add"]:
    if phrase in part6:
        raise SystemExit("Part VI incorrectly implies a Small Array growth API: "+phrase)
if "length()" not in part6 or "size()" not in part6 or "push_back" not in part6:
    raise SystemExit("Expected corrected length/size transition missing.")
if "SMALL_BEGINNER_MODE" not in header:
    raise SystemExit("Beginner namespace mechanism changed; review Part VI.")
print("Part VI API/prose consistency check passed.")

lesson34="\n".join(p.read_text(encoding="utf-8") for d in tutorial.glob("*_includes_namespaces_*") for p in d.glob("*"))
for term in ["std::cout", "std::cin", "std::getline"]:
    if term not in lesson34:
        raise SystemExit("Include/namespace lessons must teach standard console I/O: "+term)

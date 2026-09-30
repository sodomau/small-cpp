#!/usr/bin/env python3
from pathlib import Path
root=Path(__file__).resolve().parents[1]
tutorial=root/"tutorial"
part6="\n".join(p.read_text(encoding="utf-8") for d in tutorial.glob("3[2-6]_*") for p in d.glob("*.md"))
header=(root/"runtime/small.h").read_text(encoding="utf-8")
if "No Resize/Append operations." not in header:
    raise SystemExit("Expected Small Array fixed-size contract changed; review Part VI.")
for phrase in ["Add가 push_back으로", "Array.Add", "numbers.Add"]:
    if phrase in part6:
        raise SystemExit("Part VI incorrectly implies a Small Array growth API: "+phrase)
if "Length()는 size()로" not in part6:
    raise SystemExit("Expected corrected Length/size transition missing.")
if "SMALL_BEGINNER_MODE" not in header:
    raise SystemExit("Beginner namespace mechanism changed; review Part VI.")
print("Part VI API/prose consistency check passed.")

lesson34="\n".join(p.read_text(encoding="utf-8") for p in (tutorial/"34_includes_namespaces").glob("*"))
for term in ["std::cout", "std::cin", "std::getline"]:
    if term not in lesson34:
        raise SystemExit("Lesson 34 must teach standard console I/O before Lesson 36: "+term)

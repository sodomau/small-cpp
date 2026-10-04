#!/usr/bin/env python3
from pathlib import Path
import json
root=Path(__file__).resolve().parents[1]
header=(root/"runtime/small.h").read_text(encoding="utf-8")
runtime=(root/"runtime/small_runtime.cpp").read_text(encoding="utf-8")
assert "int random_int(int min, int max);" in header
assert "double random_real(double min, double max);" in header
assert "std::uniform_int_distribution<int>" in runtime
assert "std::uniform_real_distribution<double>" in runtime
assert "if (min > max)" in runtime
catalog=json.loads((root/"examples/catalog.json").read_text(encoding="utf-8"))
ids={e["id"] for e in catalog["examples"]}
assert "reference/random" in ids
assert "random_int(1, 100)" in (root/"examples/programs/number_guessing.cpp").read_text(encoding="utf-8")
print("Random API, reference example, and guessing-program checks passed.")

#!/usr/bin/env python3
from pathlib import Path
import json
import xml.etree.ElementTree as ET

root=Path(__file__).resolve().parents[1]
catalog=json.loads((root/"examples/catalog.json").read_text(encoding="utf-8"))
catalog_sources={entry["source"] for entry in catalog["examples"]}

tree=ET.parse(root/"ide/SmallExamples.qrc")
resource_sources={
    node.attrib.get("alias","")
    for node in tree.findall(".//file")
    if node.attrib.get("alias","") != "catalog.json"
}

missing=sorted(catalog_sources-resource_sources)
extra=sorted(resource_sources-catalog_sources)
if missing or extra:
    lines=[]
    if missing: lines.append("Catalog sources missing from SmallExamples.qrc: "+", ".join(missing))
    if extra: lines.append("SmallExamples.qrc sources missing from catalog: "+", ".join(extra))
    raise SystemExit("\n".join(lines))

for source in catalog_sources:
    if not (root/"examples"/source).is_file():
        raise SystemExit("Example source file is missing: "+source)

print(f"Example resource coverage OK: {len(catalog_sources)} catalog sources.")

#!/usr/bin/env python3
"""Validate bundled example metadata/resources; this is NOT API/behavior coverage."""
from pathlib import Path
import json
import re
import sys
import xml.etree.ElementTree as ET

ROOT = Path(__file__).resolve().parents[1]
EXAMPLES = ROOT / "examples"
errors = []
try:
    document = json.loads((EXAMPLES / "catalog.json").read_text(encoding="utf-8"))
    if document.get("version") != 1:
        errors.append("Unsupported catalog version")
    entries = document.get("examples", [])
    if not isinstance(entries, list) or not entries:
        raise ValueError("examples must be a nonempty array")
    sources, ids = set(), set()
    for item in entries:
        source = item.get("source", "")
        identifier = item.get("id", "")
        if not re.fullmatch(r"(reference|programs)/[a-z0-9_]+\.cpp", source):
            errors.append(f"Unsafe or invalid source path: {source!r}")
            continue
        if identifier != source[:-4] or identifier in ids or source in sources:
            errors.append(f"Duplicate/mismatched id or source: {identifier!r}")
        ids.add(identifier)
        sources.add(source)
        expected_group = "Reference" if source.startswith("reference/") else "Programs"
        if item.get("group") != expected_group:
            errors.append(f"Wrong group for {source}")
        for field in ("title", "description", "notes"):
            if not isinstance(item.get(field), str) or not item[field].strip():
                errors.append(f"{source}: missing {field}")
        concepts = item.get("concepts")
        if not isinstance(concepts, list) or not concepts or any(
                not isinstance(value, str) or not value.strip() for value in concepts):
            errors.append(f"{source}: invalid concepts")
        text = (EXAMPLES / source).read_text(encoding="utf-8")
        if "void small_main()" not in text:
            errors.append(f"{source}: no small_main entry point found")

    actual = {p.relative_to(EXAMPLES).as_posix()
              for group in ("reference", "programs")
              for p in (EXAMPLES / group).glob("*.cpp")}
    if sources != actual:
        errors.append(f"Source/catalog mismatch: unlisted={sorted(actual-sources)}, missing={sorted(sources-actual)}")
    qrc = ROOT / "ide" / "SmallExamples.qrc"
    xml = ET.parse(qrc).getroot()
    resources = xml.findall("qresource")
    if len(resources) != 1 or resources[0].get("prefix") != "/small/examples":
        errors.append("Incorrect qrc resource prefix")
    aliases = {}
    for item in xml.findall("qresource/file"):
        alias = item.get("alias")
        if alias in aliases:
            errors.append(f"Duplicate resource alias: {alias}")
        target = (qrc.parent / (item.text or "")).resolve()
        aliases[alias] = target
        if alias is not None and target != (EXAMPLES / alias).resolve():
            errors.append(f"Resource does not point to the catalog source: {alias}")
        if not target.is_file():
            errors.append(f"Missing resource file: {target}")
    expected_aliases = sources | {"catalog.json"}
    if set(aliases) != expected_aliases:
        errors.append("The qrc does not embed exactly the catalog and its example files")
except (OSError, ValueError, TypeError, AttributeError, ET.ParseError) as error:
    errors.append(str(error))

if errors:
    print("Example catalog/resource integrity FAILED")
    for error in errors:
        print(" -", error)
    sys.exit(1)

print(f"Example catalog/resource integrity passed: {len(entries)} examples")
print(f"Reference: {sum(e['group']=='Reference' for e in entries)}; Programs: {sum(e['group']=='Programs' for e in entries)}")
print("Every catalog source is present and embedded once. No external data download is used.")

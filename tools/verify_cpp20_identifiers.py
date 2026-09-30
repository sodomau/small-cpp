#!/usr/bin/env python3
from pathlib import Path
import re
root=Path(__file__).resolve().parents[1]
keywords=["concept","requires","co_await","co_return","co_yield"]
bad=[]
source_roots = [root/name for name in ("ide", "runtime", "extensions", "examples", "tutorial", "tests")]
paths = [path for directory in source_roots for pattern in ("*.cpp", "*.h")
         for path in directory.rglob(pattern)]
for path in paths:
    text=path.read_text(encoding="utf-8",errors="ignore")
    for kw in keywords:
        patterns=[
            rf"\b(?:auto|int|double|bool|QString|QJsonValue)\s+{kw}\b",
            rf"\bconst\s+auto\s*&\s*{kw}\b",
            rf"for\s*\([^;:]*\b{kw}\s*:",
        ]
        if any(re.search(pattern,text) for pattern in patterns):
            bad.append(f"{path.relative_to(root)}: {kw}")
if bad:
    raise SystemExit("C++20 keyword used as identifier:\n" + "\n".join(bad))
print("C++20 identifier collision check passed.")

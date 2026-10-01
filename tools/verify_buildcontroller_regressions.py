#!/usr/bin/env python3
from pathlib import Path
import re
text=(Path(__file__).resolve().parents[1]/"ide/BuildController.cpp").read_text(encoding="utf-8")
assert 'extension.id + "\\n" +' in text
# Every extension loop must avoid detaching Qt's implicitly shared container.
loops = re.findall(r"for \(const auto& extension : (.+)\)", text)
assert loops and all(expression == "std::as_const(extensions_)" for expression in loops)
gnu=text.index('if (QString::fromUtf8(SmallBuildConfig::CompilerId) == "GNU")')
assert "{" in text[gnu:gnu+100]
print("BuildController Windows-build regression checks passed.")

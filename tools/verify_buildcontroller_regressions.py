#!/usr/bin/env python3
from pathlib import Path
text=(Path(__file__).resolve().parents[1]/"ide/BuildController.cpp").read_text(encoding="utf-8")
assert 'extension.id + "\\n" +' in text
assert text.count("std::as_const(extensions_)") == 2
assert "for (const auto& extension : extensions_)" not in text
gnu=text.index('if (QString::fromUtf8(SmallBuildConfig::CompilerId) == "GNU")')
assert "{" in text[gnu:gnu+100]
print("BuildController Windows-build regression checks passed.")

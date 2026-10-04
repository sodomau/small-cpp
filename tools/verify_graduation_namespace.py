#!/usr/bin/env python3
from pathlib import Path
root=Path(__file__).resolve().parents[1]
controller=(root/"ide/BuildController.cpp").read_text(encoding="utf-8")
if 'if (!usesOwnMain_)' not in controller:
    raise SystemExit("Missing small_main/main compilation split.")
block=controller.split('if (!usesOwnMain_)',1)[1].split('}',1)[0]
for required in ['-DSMALL_BEGINNER_MODE','-include','small.h']:
    if required not in block:
        raise SystemExit("small_main path missing hidden convenience: "+required)
prefix=controller.split('if (!usesOwnMain_)',1)[0].split('void BuildController::compile()',1)[1]
if '"-include"' in prefix:
    raise SystemExit("small.h is still force-included for real main().")
manual=(root/"tests/test_manual_main.cpp").read_text(encoding="utf-8")
for required in ['#include <small.h>','Small::initialize_small','Small::print']:
    if required not in manual:
        raise SystemExit("Manual-main regression test is incomplete: "+required)
for p in (root/"tutorial/35_smallmain").glob("*.cpp"):
    if '#include <small.h>' not in p.read_text(encoding="utf-8"):
        raise SystemExit("Lesson 35 main source lacks explicit <small.h>: "+p.name)
for p in (root/"tutorial/36_beyond").glob("*.cpp"):
    if 'small.h' in p.read_text(encoding="utf-8").lower():
        raise SystemExit("Lesson 36 must be Small-free: "+p.name)
print("Graduation include/namespace policy check passed.")

#!/usr/bin/env python3
from pathlib import Path
root=Path(__file__).resolve().parents[1]
files=[root/"examples/programs/pong.cpp",
       root/"tutorial/18_game/example1.cpp",
       root/"tutorial/18_game/example2.cpp",
       root/"tutorial/18_game/exercise2_starter.cpp",
       root/"tutorial/18_game/exercise2_solution.cpp"]
bad=["if (ballY < 10 || ballY > 490)",
     "if (ballX > 790)\\n            ballVX",
     "if (ballX < 15 || ballX > 625)",
     "if (ballY < 20)\\n            ballVY"]
for p in files:
    text=p.read_text(encoding="utf-8")
    for pattern in bad:
        if pattern in text:
            raise SystemExit(f"Uncorrected collision response in {p}: {pattern}")
print("Collision example position-correction check passed.")

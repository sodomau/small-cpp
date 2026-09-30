#!/usr/bin/env python3
from pathlib import Path
root=Path(__file__).resolve().parents[1]
files=[root/"examples/programs/pong.cpp",
       *sorted((root/"tutorial/52_game_1").glob("*.cpp")),
       *sorted((root/"tutorial/53_game_2").glob("*.cpp"))]
assert len(files) == 7, "Both current game lessons must supply example/starter/solution"
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

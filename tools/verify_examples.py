#!/usr/bin/env python3
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
REF = ROOT / "examples" / "reference"

coverage = {
    "console.cpp": ["Print(", "Write(", "Input(", "InputInt(", "InputReal(", "Format("],
    "string.cpp": ["Length(", "Substring(", "a[0]", " + ", "+=", "==", "!=", "<", "<=", ">", ">="],
    "array.cpp": ["Array<int> a(5)", "Array<int> b =", "Length(", "a[0]", "a = b", "Array<bool>"],
    "file.cpp": ["File ", "FileMode::Read", "FileMode::Write", "FileMode::Append",
                 "FileMode::ReadBinary", "FileMode::WriteBinary", ".Close(", ".IsOpen(", ".End(",
                 ".Input(", ".InputInt(", ".InputReal(", ".Write(", ".Print(",
                 ".ReadInt(", ".ReadReal(", ".WriteInt(", ".WriteReal("],
    "drawing.cpp": ["RGB(", "Black", "White", "Red", "Green", "Blue", "Yellow", "Cyan", "Magenta", "Gray",
                    ".Open(", ".Clear(", ".SetPixel(", ".DrawLine(", ".DrawRectangle(", ".FillRectangle(",
                    ".DrawCircle(", ".FillCircle(", ".DrawText(", ".Show("],
    "window.cpp": [".SetTitle(", ".Title(", ".Close(", ".IsOpen(", ".Width(", ".Height("],
    "keyboard.cpp": ["Key::Left","Key::Right","Key::Up","Key::Down","Key::Space","Key::Enter",
                     "Key::Escape","Key::Tab","Key::Backspace","Key::Delete",
                     ".KeyDown(", ".KeyPressed(", ".KeyReleased("],
    "mouse.cpp": ["MouseButton::Left","MouseButton::Right","MouseButton::Middle",
                  ".MouseX(", ".MouseY(", ".MouseDown(", ".MousePressed(", ".MouseReleased("],
    "stopwatch.cpp": ["StopWatch", ".Elapsed(", ".Reset("],
    "timer.cpp": ["Timer", ".Start(", ".Stop(", ".IsRunning(", "OnTimer"],
    "sound.cpp": ["Sound::Click","Sound::Pop","Sound::Jump","Sound::Hit","Sound::Coin","Sound::Shoot",
                  "Sound::Explosion","Sound::Win","Sound::Lose","PlaySound(","PlaySoundAndWait(",
                  "Beep(","BeepAndWait("],
    "cpp_interop.cpp": ["Small::String", "std::cout", ".c_str(", "std::sqrt", "Small::Print"],
}

missing = []
for filename, tokens in coverage.items():
    path = REF / filename
    if not path.exists():
        missing.append(f"{filename}: file missing")
        continue
    text = path.read_text(encoding="utf-8")
    for token in tokens:
        if token not in text:
            missing.append(f"{filename}: missing {token}")

if missing:
    print("REFERENCE COVERAGE FAILED")
    for item in missing: print(" -", item)
    sys.exit(1)

print(f"Reference coverage OK: {len(coverage)} files")
print("All learner-facing API groups and learner enum values are represented.")

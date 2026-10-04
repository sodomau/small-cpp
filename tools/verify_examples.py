#!/usr/bin/env python3
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
REF = ROOT / "examples" / "reference"

coverage = {
    "console.cpp": ["print(", "write(", "input(", "input_int(", "input_real(", "format("],
    "string.cpp": ["length(", "substring(", "a[0]", " + ", "+=", "==", "!=", "<", "<=", ">", ">="],
    "array.cpp": ["Array<int> a(5)", "Array<int> b =", "length(", "a[0]", "a = b", "Array<bool>"],
    "file.cpp": ["File ", "FileMode::Read", "FileMode::Write", "FileMode::Append",
                 "FileMode::ReadBinary", "FileMode::WriteBinary", ".close(", ".is_open(", ".end(",
                 ".input(", ".input_int(", ".input_real(", ".write(", ".print(",
                 ".read_int(", ".read_real(", ".write_int(", ".write_real("],
    "drawing.cpp": ["rgb(", "Black", "White", "Red", "Green", "Blue", "Yellow", "Cyan", "Magenta", "Gray",
                    ".open(", ".clear(", ".set_pixel(", ".draw_line(", ".draw_rectangle(", ".fill_rectangle(",
                    ".draw_circle(", ".fill_circle(", ".draw_text(", ".show("],
    "window.cpp": [".set_title(", ".title(", ".close(", ".is_open(", ".width(", ".height("],
    "keyboard.cpp": ["Key::Left","Key::Right","Key::Up","Key::Down","Key::Space","Key::Enter",
                     "Key::Escape","Key::Tab","Key::Backspace","Key::Delete",
                     ".key_down(", ".key_pressed(", ".key_released("],
    "mouse.cpp": ["MouseButton::Left","MouseButton::Right","MouseButton::Middle",
                  ".mouse_x(", ".mouse_y(", ".mouse_down(", ".mouse_pressed(", ".mouse_released("],
    "stopwatch.cpp": ["StopWatch", ".elapsed(", ".reset("],
    "timer.cpp": ["Timer", ".start(", ".stop(", ".is_running(", "on_timer"],
    "sound.cpp": ["Sound::Click","Sound::Pop","Sound::Jump","Sound::Hit","Sound::Coin","Sound::Shoot",
                  "Sound::Explosion","Sound::Win","Sound::Lose","play_sound(","play_sound_and_wait(",
                  "beep(","beep_and_wait("],
    "cpp_interop.cpp": ["Small::String", "std::cout", ".c_str(", "std::sqrt", "Small::print"],
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

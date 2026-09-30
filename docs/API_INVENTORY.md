# Phase 3A — Learner API Inventory & Example Specification

Coverage means **learner-facing Small C++ vocabulary**, not every technically public C++ member.

Interfaces are classified as:
- **Learner** — should appear in reference examples/tutorials.
- **Advanced / Interop** — intentionally hidden until the C++ bridge material.
- **Implementation / constraint** — may be public for C++ reasons but is not taught as a feature.

## 1. String

### Beginner-facing
| API | Planned reference example |
|---|---|
| `String()` | `reference/string.cpp` |
| `String(const char*)` via `String s = "Hello";` | `reference/string.cpp` |
| copy / assignment | `reference/string.cpp` |
| `Length()` | `reference/string.cpp` |
| `operator[]` read | `reference/string.cpp` |
| `operator[]` write | `reference/string.cpp` |
| `Substring(start)` | `reference/string.cpp` |
| `Substring(start, length)` | `reference/string.cpp` |
| `operator+` | `reference/string.cpp` |
| `operator+=` | `reference/string.cpp` |
| `== != < <= > >=` | `reference/string.cpp` |
| literal-on-left comparisons | `reference/string.cpp` |
| printing through `Print` / `Write` | `reference/string.cpp` |

### Interoperability / implementation-facing
| API | Planned example |
|---|---|
| `String(const std::string&)` — implicit inbound conversion only | `reference/cpp_interop.cpp` |
| `String(const char*, int)` | `reference/cpp_interop.cpp` |
| `c_str()` | `reference/cpp_interop.cpp` |
| `operator<<` | `reference/cpp_interop.cpp` |

**v1 audit note:** these three are public today because they bridge Small and ordinary C++. Keep them out of the beginner tutorial. Reconsider whether the length constructor should remain public before final v1 freeze.

## 2. Array<T>

| API | Planned reference example |
|---|---|
| `Array()` | `reference/array.cpp` |
| `Array(length)` | `reference/array.cpp` |
| initializer-list construction | `reference/array.cpp` |
| copy / assignment, including different lengths | `reference/array.cpp` |
| `Length()` | `reference/array.cpp` |
| `operator[]` read | `reference/array.cpp` |
| `operator[]` write | `reference/array.cpp` |
| `Array<bool>` real-reference behavior | `reference/array.cpp` |

No `Resize`, `Append`, or pointer API is part of Small Array.

## 3. Console

| API | Planned reference example |
|---|---|
| `Print()` | `reference/console.cpp` |
| `Print(args...)` | `reference/console.cpp` |
| `Format(args...)` — build a `String` with Print-like arguments | `reference/console.cpp` |
| `Write()` / `Write(args...)` | `reference/console.cpp` |
| `Input()` | `reference/console.cpp` |
| `Input(prompt)` | `reference/console.cpp` |
| `InputInt()` / `InputInt(prompt)` | `reference/console.cpp` |
| `InputReal()` / `InputReal(prompt)` | `reference/console.cpp` |

Program console is a real native console; the IDE lower pane is diagnostics only.


## File

### Learner-facing
| API | Reference example |
|---|---|
| `File` | `reference/file.cpp` |
| `Open(filename)` | `reference/file.cpp` |
| `Open(filename, FileMode::Read)` | `reference/file.cpp` |
| `Open(filename, FileMode::Write)` | `reference/file.cpp` |
| `Open(filename, FileMode::Append)` | `reference/file.cpp` |
| `Open(filename, FileMode::ReadBinary)` | `reference/file.cpp` |
| `Open(filename, FileMode::WriteBinary)` | `reference/file.cpp` |
| `Close()` | `reference/file.cpp` |
| `IsOpen()` | `reference/file.cpp` |
| `End()` | `reference/file.cpp` |
| `Input()` | `reference/file.cpp` |
| `InputInt()` | `reference/file.cpp` |
| `InputReal()` | `reference/file.cpp` |
| `Write(...)` | `reference/file.cpp` |
| `Print(...)` | `reference/file.cpp` |
| `ReadInt()` — native `int` representation | `reference/file.cpp` |
| `ReadReal()` — native `double` representation | `reference/file.cpp` |
| `WriteInt(int)` — native `int` representation | `reference/file.cpp` |
| `WriteReal(double)` — native `double` representation | `reference/file.cpp` |

`File` is RAII-safe internally: destruction closes an open file, while learners still use explicit `Open` / `Close` because it matches the real-world model.


## 4. Color

| API | Planned reference example |
|---|---|
| `RGB(r,g,b)` | `reference/color.cpp` |
| `Red()` / `Green()` / `Blue()` | `reference/color.cpp` |
| `Black White Red Green Blue Yellow Cyan Magenta Gray` | `reference/color.cpp` |
| default `Color()` | `reference/color.cpp` |

`SetRGB()` is public today but `RGB()` is the intended beginner constructor vocabulary.

**v1 audit note:** consider hiding `SetRGB()` before final API freeze if no compelling educational use appears.

## 5. Keyboard

`Key::{Left, Right, Up, Down, Space, Enter, Escape, Tab, Backspace, Delete}`

| API | Planned reference example |
|---|---|
| `KeyDown(Key)` | `reference/keyboard.cpp` |
| `KeyPressed(Key)` | `reference/keyboard.cpp` |
| `KeyReleased(Key)` | `reference/keyboard.cpp` |
| `KeyDown(char)` | `reference/keyboard.cpp` |
| `KeyPressed(char)` | `reference/keyboard.cpp` |
| `KeyReleased(char)` | `reference/keyboard.cpp` |

The example will exercise every named `Key` value at least once, without making the program artificially complicated.

## 6. Mouse

`MouseButton::{Left, Right, Middle}`

| API | Planned reference example |
|---|---|
| `MouseX()` / `MouseY()` | `reference/mouse.cpp` |
| `MouseDown(button)` | `reference/mouse.cpp` |
| `MousePressed(button)` | `reference/mouse.cpp` |
| `MouseReleased(button)` | `reference/mouse.cpp` |

Every mouse button value will appear.

## 7. Window / Graphics

### Lifetime and size
| API | Planned reference example |
|---|---|
| `Window()` | `reference/drawing.cpp` |
| `Open(width,height)` | `reference/drawing.cpp` |
| `SetTitle(args...)` — Print-like arguments; valid before or after `Open()` | `reference/window.cpp` |
| `Title()` — valid even while closed | `reference/window.cpp` |
| `Close()` | `reference/window.cpp` |
| `IsOpen()` | `reference/window.cpp` |
| `Width()` / `Height()` | `reference/window.cpp` |

### Drawing
| API | Planned reference example |
|---|---|
| `Clear()` | `reference/drawing.cpp` |
| `SetPixel()` | `reference/drawing.cpp` |
| `DrawLine()` | `reference/drawing.cpp` |
| `DrawRectangle()` | `reference/drawing.cpp` |
| `FillRectangle()` | `reference/drawing.cpp` |
| `DrawCircle()` | `reference/drawing.cpp` |
| `FillCircle()` | `reference/drawing.cpp` |
| `DrawText(x,y,text)` | `reference/drawing.cpp` |
| `DrawText(x,y,text,color,size)` | `reference/drawing.cpp` |
| `Show()` | `reference/drawing.cpp` |

Copying Window is intentionally unsupported and is not a learner operation.

## 8. Time

### StopWatch
| API | Planned reference example |
|---|---|
| construction starts timing | `reference/stopwatch.cpp` |
| `Elapsed()` | `reference/stopwatch.cpp` |
| `Reset()` | `reference/stopwatch.cpp` |

### Timer
| API | Planned reference example |
|---|---|
| `Start(interval, callback)` | `reference/timer.cpp` |
| `Stop()` | `reference/timer.cpp` |
| `IsRunning()` | `reference/timer.cpp` |

The callback example uses a plain `void OnTimer()` function first, so event-based programming appears before lambdas or `std::function`.

### Sleep
| API | Planned reference example |
|---|---|
| `Sleep(seconds)` | `reference/time.cpp` |

## 9. Sound

`Sound::{Click, Pop, Jump, Hit, Coin, Shoot, Explosion, Win, Lose}`

| API | Planned reference example |
|---|---|
| `PlaySound()` | `reference/sound.cpp` |
| `PlaySoundAndWait()` | `reference/sound.cpp` |
| `Beep()` | `reference/sound.cpp` |
| `BeepAndWait()` | `reference/sound.cpp` |

The sound example will play every preset once.

## 10. Entry point and namespace

| API / concept | Planned reference example |
|---|---|
| global `void SmallMain()` | every example |
| `namespace Small` | `reference/cpp_interop.cpp` |
| `SMALL_BEGINNER_MODE` behavior | documentation/test, not learner code |
| explicit `Small::Window`, `Small::Print`, etc. | `reference/cpp_interop.cpp` |

## Phase 3B planned reference set

```text
examples/
└─ reference/
   ├─ console.cpp
   ├─ string.cpp
   ├─ array.cpp
   ├─ file.cpp
   ├─ window.cpp
   ├─ drawing.cpp
   ├─ keyboard.cpp
   ├─ mouse.cpp
   ├─ time.cpp
   ├─ stopwatch.cpp
   ├─ timer.cpp
   ├─ sound.cpp
   └─ cpp_interop.cpp
```

## Phase 3C planned program examples

```text
examples/
└─ programs/
   ├─ ascii_art.cpp
   ├─ number_guessing.cpp
   ├─ drawing_pad.cpp
   ├─ bouncing_ball.cpp
   ├─ reaction_timer.cpp
   ├─ pong.cpp
   └─ save_game.cpp
```

These are for motivation and composition, not API completeness.

## Coverage policy

1. Every beginner-facing public operation must appear in at least one reference example.
2. Every enum value intended for learners must appear in at least one reference example.
3. Public interop operations must appear in `cpp_interop.cpp`.
4. Every reference example must compile.
5. An API change is incomplete until its example mapping is updated.
6. Fun/program examples are never used as the sole coverage for a core API.


## Graduation / interoperability entry point

| API | Classification | Tutorial |
|---|---|---|
| `InitializeSmall()` | Advanced / Interop | Lesson 35 |
| `InitializeSmall(argc, argv)` | Advanced / Interop | Lesson 35 |

`SmallMain()` remains the beginner entry point. A learner-written top-level `main()` is detected automatically by the IDE and takes precedence. No mode switch is exposed.

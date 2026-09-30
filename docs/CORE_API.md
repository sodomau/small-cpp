# Small C++ Core API — v1 Candidate

Phase 1 freezes the core conceptually: keep it small and move domain-specific teaching features to extensions.

- Values: String, Array<T>
- Console: Print, Write, Input, InputInt, InputReal
- File: Open/Close, Read/Write/Append plus ReadBinary/WriteBinary, Input/InputInt/InputReal, Print/Write, End
- Graphics: Color, RGB, Window, drawing primitives, DrawText, Show
- Input: Key and MouseButton with Down / Pressed / Released
- Time: StopWatch, Timer, Sleep
- Sound: Sound presets, PlaySound, PlaySoundAndWait, Beep, BeepAndWait
- Entry point: global void SmallMain()
- Namespace: API lives in Small; SMALL_BEGINNER_MODE enables using namespace Small

StopWatch is intentionally a real-world stopwatch abstraction: construction starts measurement, Elapsed reads it, and Reset starts again from zero.

Turtle, plotting, image processing, music, physics, robotics, and similar domain features should normally be extensions.

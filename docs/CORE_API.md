# Small C++ Core API — v1 Candidate

Phase 1 freezes the core conceptually: keep it small and move domain-specific teaching features to extensions.

- Values: String, Array<T>
- Console: `print`, `write`, `input`, `input_int`, `input_real`
- File: `open`/`close`, FileMode values Read/Write/Append plus ReadBinary/WriteBinary, `input`/`input_int`/`input_real`, `print`/`write`, `end`
- Graphics: Color, `rgb`, Window, drawing primitives, `draw_text`, `show`
- Input: Key and MouseButton with Down / Pressed / Released
- Time: StopWatch, Timer, `sleep`
- Sound: Sound presets, play_sound, play_sound_and_wait, beep, beep_and_wait
- Entry point: global void small_main()
- Namespace: API lives in Small; SMALL_BEGINNER_MODE enables using namespace Small

StopWatch is intentionally a real-world stopwatch abstraction: construction starts measurement, `elapsed()` reads it, and `reset()` starts again from zero.

Turtle, plotting, image processing, music, physics, robotics, and similar domain features should normally be extensions.

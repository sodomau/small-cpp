# Phase 3A API Audit

The inventory found three areas worth consciously deciding before the final v1 API freeze.

## 1. String interoperability surface
`String(const char*, int)`, `c_str()`, and `operator<<` are useful bridges to ordinary C++, but they are not beginner vocabulary. Keep them out of early tutorials and demonstrate them only in the C++ interoperability example.

## 2. Color::set_rgb
The intended beginner expression is `Color c = rgb(10, 20, 30);`. `set_rgb()` is currently public mainly because of implementation history. Before v1, decide whether mutable colors are pedagogically useful. If not, make it non-public and keep Color as a simple value.

## 3. Window and Timer non-copyability
Deleted copy operations are correct C++ design constraints, but not learner-facing API. They should be documented under the hood rather than demonstrated as normal usage.

No other core API currently looks obviously out of scope. The core remains small: values, console, graphics/input, time/events, and sound.

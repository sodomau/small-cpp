# Small C++ Educational Diagnostics — Phase 2

The IDE shows a short learner-facing explanation first and keeps the original C++ compiler output behind **Show C++ Error**.

## Compile-time cases covered

- missing semicolon
- assignment used as a condition (`=` vs `==`)
- missing condition parentheses
- missing `]`, `)`, `{`, `}`
- unknown name and unknown type
- invalid Array/String indexing
- type mismatch
- wrong number/type of function arguments
- duplicate definitions
- `else` without a matching `if`
- `break` / `continue` outside loops
- unknown object member
- access to a private member
- invalid operators for the supplied types
- calling a non-function
- malformed code position / likely punctuation error
- wrong return value
- missing `SmallMain`

## Runtime cases covered

- Array and String index range errors
- Substring range errors
- negative Array length
- invalid RGB values
- Window used before `Open`
- invalid Window size / pixel position
- invalid rectangle, circle, and text sizes
- invalid Sleep, Timer, and Beep arguments
- missing Timer callback
- input ending unexpectedly

Runtime source lines are shown only when the IDE can infer a unique matching operation. The UI explicitly labels such a location as inferred rather than claiming an exact stack location.

## Design rule

Diagnostics should explain the programming mistake, not teach compiler jargon. The original diagnostic always remains available so learners can gradually become familiar with real C++ compiler messages.

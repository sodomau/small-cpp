# Binary File Representation

Small C++ binary file I/O deliberately follows native C++ representation.

- `WriteInt(x)` writes the `sizeof(int)` bytes of `x` as represented by the current C++ implementation.
- `ReadInt()` reads `sizeof(int)` bytes into an `int`.
- `WriteReal(x)` writes the `sizeof(double)` bytes of `x`.
- `ReadReal()` reads `sizeof(double)` bytes into a `double`.

Small does not define its own endian conversion, integer width, floating-point wire format, or portable serialization format.

This is intentional: binary File is a simple wrapper around ordinary native C++ binary I/O. Portability issues such as `sizeof`, byte order, floating-point representation, and structured file formats are concepts to expose later rather than silently normalize here.

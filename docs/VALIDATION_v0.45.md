# Validation — v0.45

- Image API is absent from core `small.h`.
- Image extension header includes core and declares free `DrawImage` relationships.
- IDE registry detects `<small/image.h>` and generated build config supplies the separate image library filename.
- SDK packaging includes `small/image.h` and the precompiled image extension library.
- Existing tutorial, UI packaging, and build-config checks pass.
- Full Image compile/link/run requires the Windows Qt/MinGW kit because the implementation uses Qt QImage.

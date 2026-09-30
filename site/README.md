# Small C++ project page

A responsive, English/Korean introduction to the native desktop IDE. This is
a local preview, not a published website. It uses the existing logo and real
IDE screenshots; the IDE itself remains a native Qt application.

From the repository root, run:

```powershell
python -X utf8 tools/preview_site.py
```

Open http://127.0.0.1:8765. Use `--port` to select another port or `--build-only`
to prepare the static files without starting the server. Generated files and
copied artwork stay under `build/project-page/`. The server binds only to the
local computer. Stop it with Ctrl+C.

The build renders all 91 lessons in both languages as static HTML, including
the shared examples, exercise starters, and collapsible solutions. The lesson
index and previous/next links work without a Markdown viewer or extra packages.
Generated pages remain in `build/`; the original lesson content is unchanged.
The preview server serves only the generated site directory. The download button
points to the existing v0.76.9 preview and does not imply the English pack is
included in that binary. No external fonts, scripts, or analytics are loaded.

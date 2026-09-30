#!/usr/bin/env python3
from pathlib import Path
root=Path(__file__).resolve().parents[1]
text=(root/"runtime/small_runtime.cpp").read_text(encoding="utf-8")
public=text.split("void BlitRgba(Window& window",1)[1]
assert "Window::Impl*" not in public, "BlitRgba names private Window::Impl outside its friend."
assert "WindowAccess::BlitRgba" in public
access=text.split("struct WindowAccess",1)[1].split("};",1)[0]
assert "window.impl_->back" in access
print("WindowAccess private-implementation boundary check passed.")

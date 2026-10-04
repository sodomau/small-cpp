# Small C++ for Windows

1. Extract the entire ZIP into a folder you can write to, such as Documents/SmallCpp.
2. Open `SmallCppIDE.exe` inside that folder. Do not run it from inside the ZIP.
3. Enter this program and press **Run** (F5):

```cpp
void small_main()
{
    print("Hello, Small C++!");
}
```

Use **Learn → Tutorial...** for the 88 Korean/English lessons and **Learn → Examples...**
for runnable examples. **Settings → Theme** offers Light, Dark and custom `.qss` files.
The compiler and debugger are included; no separate Qt or compiler installation is needed.

## 한국어

ZIP 전체를 문서 폴더 등의 쓰기 가능한 위치에 압축 해제한 다음
`SmallCppIDE.exe`를 실행하세요. ZIP 안에서 바로 실행하지 마세요.
위 코드를 입력하고 **Run** 또는 F5를 누르면 첫 프로그램이 실행됩니다.
**Learn → Tutorial...**에서 한국어 레슨을 시작할 수 있습니다.

## Requirements and licenses

This package targets 64-bit Windows on an x86-64 CPU. Windows 11 is the current
Qt-supported development target. It is an unsigned early public release.

Small C++ project code, lessons and assets use the MIT License (`LICENSE`).
Qt libraries and bundled tools retain their own licenses. Read
`licenses/THIRD_PARTY.txt` and `licenses/SOURCE_ACCESS.md` for notices, source
archives and instructions for rebuilding/replacing libraries. The package uses
Qt's native Windows multimedia backend for Small's generated PCM sounds and
does not bundle FFmpeg or the optional software OpenGL renderer.

Report problems with reproduction steps at https://github.com/sodomau/small-cpp/issues.

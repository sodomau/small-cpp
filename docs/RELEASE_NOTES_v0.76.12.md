## Windows portable preview

Download **SmallCpp-v0.76.12-Windows-x64.zip**, extract the entire ZIP, and open **SmallCppIDE.exe**. Windows x64 is required; Qt and the compiler/debugger are included.

### What's new

- The learner API now consistently uses snake_case: `small_main`, `print`, `input_int`, `window.open`, `window.key_pressed`, `watch.elapsed`, and `load_image`. Types such as `Window`, enum values, and named colors such as `White` retain their names.
- Examples, Korean/English tutorials, code highlighting, API reference, and beginner error explanations follow the new names.
- The project website has current light/dark IDE screenshots and a lesson index organized into eight collapsible core parts plus the Image extension, covering all 100 lessons.

### Updating existing programs

**This release changes API names and removes the previous PascalCase function names.** For example, change `SmallMain` to `small_main`, `Print` to `print`, and `window.Open` to `window.open`. See `docs/NAMING_CONVENTIONS.md` in the package for the naming rules and migration examples. Earlier release ZIPs remain available for older programs.

Use the tutorials included with this release or the current website: their examples use the same API as this download.

### Verification and sources

The Release build and all 33 CTest checks passed. Package-only compiler/runtime checks passed for console output, ordinary C++ main, graphics, sound, Image, and both multi-file sample projects; portable IDE startup was also checked. These checks ran on the development machine with developer tool paths removed, not a separate clean Windows PC. This remains an early preview.

**SmallCpp-v0.76.12-ThirdPartySources.zip** supplies the corresponding Qt/toolchain sources and build records. Small C++ source is available in GitHub's source archives. License texts and replacement/rebuild information are included under `licenses/`. **SHA256SUMS.txt** lists both archive hashes.

새 snake_case API와 한국어·영어 튜토리얼을 포함한 Windows 포터블 미리보기입니다. ZIP 전체를 풀고 SmallCppIDE.exe를 실행하세요. 기존 코드의 PascalCase 함수 이름은 새 이름으로 수정해야 합니다.

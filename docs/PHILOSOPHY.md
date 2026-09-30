# Small C++ Design & Education Philosophy

## 1. Small C++ is C++

Small C++은 새로운 언어가 아니다.

```cpp
void SmallMain()
{
    int x = 10;

    if (x > 5)
        Print("Large");
}

```

`Print()` 같은 일부 vocabulary만 Small이 제공할 뿐, 학생이 사용하는 문법과 type system은 처음부터 실제 C++이다.

따라서 목표는:

> **Small을 배운 뒤 C++을 다시 배우지 않는 것.**

Small에서 배운 지식을 나중에 버리거나 교정할 필요가 없어야 한다.

---

## 2. Hide complexity until it becomes worth learning

Small의 가장 중요한 교육 원칙.

> **복잡성을 없애는 것이 아니라, 그것을 배울 이유가 생길 때까지 숨긴다.**

처음에는:

```cpp
void SmallMain()
{
    Print("Hello!");
}

```

만 알면 된다.

나중에는 그 뒤에:

```cpp
int main(...)
{
    ...
    SmallMain();
}

```

이 있었다는 것을 배운다.

처음에는:

```cpp
Window window;

```

라고 쓰지만 나중에는 이것이:

```cpp
Small::Window window;

```

였으며 Small IDE가 beginner mode에서:

```cpp
using namespace Small;

```

을 제공했다는 것을 배운다.

**숨겨진 것은 언젠가 공개될 수 있어야 한다.**

---

## 3. Teach complexity when the student has a reason to care

언어 specification의 순서가 아니라 **필요성이 생기는 순서**로 가르친다.

한 파일짜리 프로그램이 충분할 때는 project를 가르치지 않는다.

코드가 길어져서:

> “Player 코드를 따로 빼고 싶은데?”

라는 생각이 들 때 header와 multiple source file을 소개한다.

여러 파일을 사용해본 뒤에:

> “이 파일들을 누가 compile하고 합치는 거지?”

라는 질문이 생기면 compiler, linker, CMake를 소개한다.

즉:

```text
필요성
  ↓
개념
  ↓
도구

```

의 순서를 지킨다.

---

## 4. Prefer familiar real-world mental models

이미 현실 세계에 좋은 개념이 있다면 software-specific abstraction을 새로 만들지 않는다.

그래서:

```cpp
StopWatch watch;

Print(watch.Elapsed());
watch.Reset();

```

은 실제 스톱워치처럼 동작한다.

`File`도:

```cpp
File file;

file.Open("data.txt");
...
file.Close();

```

처럼 현실의 파일을 열고 닫는 mental model을 따른다.

`Window`도:

```cpp
Window window;
window.Open(640, 480);

```

처럼 **window라는 객체를 만드는 것**과 **실제 창을 여는 행동**을 구분한다.

설명을 듣기 전에 코드만 읽어도 의미를 짐작할 수 있어야 한다.

---

## 5. Constructors should construct, not perform surprising actions

constructor는 객체의 **개념적 생성에 필요한 일**을 한다.

그래서:

```cpp
Array<int> a(10);

```

은 자연스럽다. 길이 10은 그 Array 자체의 성질이기 때문이다.

하지만:

```cpp
Window window(640, 480);

```

보다는:

```cpp
Window window;
window.Open(640, 480);

```

을 선호한다.

OS 창을 실제로 여는 것은 construction 이상의 행동이기 때문이다.

편의성 때문에 constructor에서 추가 작업을 할 수는 있지만, **놀라운 side effect를 기본으로 만들지 않는다.**

---

## 6. Give beginners one good way first

C++의 문제 중 하나는 같은 일을 하는 방법이 너무 많다는 것이다.

Small은 가능한 한 **처음에는 하나의 좋은 표현만 보여준다.**

예:

```cpp
Color orange = RGB(255, 128, 0);

```

를 가르친다면:

```cpp
Color orange;
orange.SetRGB(...);

```

를 굳이 동시에 가르치지 않는다.

`String`도:

```cpp
String name = "Alice";

```

를 가르치지:

```cpp
String name("Alice");

```

를 처음부터 가르칠 이유가 없다.

선택지는 필요해졌을 때 늘린다.

---

## 7. Public C++ API is not the same as learner vocabulary

구현상의 이유로 public인 interface까지 전부 학생에게 보여줄 필요는 없다.

Small API를 세 층으로 생각한다.

**Learner API**

```text
Length
Substring
Print
Window
File
StopWatch
...

```

적극적으로 tutorial/example에서 사용한다.

**Advanced / Interop API**

```text
c_str()
operator<<
Small::
std::

```

일반 C++과 연결할 때 보여준다.

**Implementation / Constraint API**

C++ 구현상 public이거나 deleted operation 등으로 나타나더라도 학습 vocabulary에는 포함하지 않는다.

따라서 목표는:

> **Public API coverage 100%가 아니라 learner vocabulary coverage 100%.**

---

## 8. Use OOP when it solves a real problem

OOP는 목적이 아니다.

inheritance, virtual function, class hierarchy가 실제 문제를 해결할 때 사용한다.

단순한 문제를:

```text
Interface
→ AbstractFactory
→ Manager
→ Implementation

```

같은 구조로 만들 이유가 없다.

반대로 global callback을 object state와 연결해야 하는 것처럼 OOP가 문제를 깔끔하게 해결한다면 적극적으로 사용한다.

> **Abstraction must earn its existence.**

---

## 9. Simple outside, proper C++ inside

학생에게 단순하게 보이게 하기 위해 내부 설계를 엉성하게 만들지 않는다.

예를 들어 `File`은:

```cpp
file.Open(...);
...
file.Close();

```

라고 명시적으로 사용하지만, `Close()`를 잊어도 destructor에서 resource를 정리한다.

즉 RAII는 내부에서 정상적으로 사용한다.

namespace도 정상적으로:

```cpp
namespace Small
{
    ...
}

```

에 넣는다.

학생에게 숨긴다고 해서 내부까지 beginner code처럼 만들지 않는다.

---

## 10. Never create a dead-end abstraction

Small abstraction은 나중에 버려야 하는 가짜 개념이어서는 안 된다.

```cpp
Array<int>

```

에서:

```cpp
std::vector<int>

```

로 갈 수 있어야 하고,

```cpp
String

```

에서:

```cpp
std::string

```

으로 갈 수 있어야 한다.

Small과 standard C++도 함께 사용할 수 있어야 한다.

```cpp
#include <cmath>

void SmallMain()
{
    double x = std::sqrt(2.0);

    Print(x);
}

```

Small과 C++ 사이에 언어적 경계가 없어야 한다.

---

## 11. Growing beyond Small is success; leaving Small is optional

Small의 목표는 학생을 Small 안에 가두는 것이 아니다. 동시에 Small을 반드시 떠나게 하는 것도 목표가 아니다.

궁극적으로:

```cpp
#include <iostream>
#include <vector>

int main()
{
    ...
}

```

를 자연스럽게 읽고 쓸 수 있게 하는 것이 목표다.

따라서 tutorial 후반부에서는 의도적으로 Small의 껍질을 벗긴다.

```text
SmallMain
→ main

Window
→ Small::Window

Array
→ std::vector

String
→ std::string

Print
→ std::cout

```

Small 없이도 C++을 사용할 수 있게 되는 것은 **성장**이다. 하지만 Small API나 Extension이 편하다면 계속 사용해도 좋다.

> **Growing beyond Small is success; leaving Small is optional.**

---

## 12. Introduce real C++ concepts inside the Small curriculum

Small API를 모두 배우고 나서 C++을 시작하지 않는다.

중간에 자연스럽게:

```cpp
struct Player
{
    double x;
    double y;
};

```

를 배우고,

그다음:

```cpp
class Player
{
public:
    void Move();

private:
    double x;
    double y;
};

```

를 배운다.

학생은 이미:

```cpp
window.Open();
timer.Reset();
name.Length();

```

를 사용해왔으므로:

> “Window도 class였구나.”

라는 식으로 기존 경험과 새 개념이 연결된다.

---

## 13. Preserve the physicality of native programming

Small은 가능한 한 **실제 컴퓨터에서 실제 프로그램을 만든다는 감각**을 유지한다.

학생이 Run을 누르면:

```text
.cpp
 ↓
native compiler
 ↓
machine code
 ↓
executable

```

이 만들어진다.

`Print()`는 실제 console에 출력한다.

`File`은 실제 filesystem에 파일을 만든다.

```cpp
file.WriteInt(x);

```

하면 실제 bytes가 디스크에 기록된다.

이런 경험 자체가 교육의 일부다.

---

## 14. Do not unnecessarily normalize native C++ behavior

Binary File이 좋은 예다.

Small만의 portable serialization format을 정의하지 않는다.

```cpp
WriteInt(x)

```

는:

```text
sizeof(int) bytes

```

를 native representation 그대로 기록한다.

`WriteReal()`도 native `double` representation을 사용한다.

그 결과 나중에:

- `sizeof`
   
- byte representation
   
- endianness
   
- portability
   
- file format
   

을 배울 실제 이유가 생긴다.

> **Small should simplify C++, not pretend C++ works differently.**

---

## 15. Console and graphics are different output devices

학생 프로그램의 console을 IDE의 diagnostic panel과 섞지 않는다.

```cpp
Print(...)
Input(...)

```

은 실제 console.

```cpp
Window

```

는 graphics window.

IDE 하단은:

```text
Compile Error
Runtime Error
Diagnostics

```

만 보여준다.

학생 입장에서는:

> `Print` → text screen
>
> `Window` → graphics screen

이라는 단순한 mental model을 갖는다.

ASCII art, text adventure도 자연스럽게 만들 수 있다.

---

## 16. Errors are part of the curriculum

좋은 교육환경은 올바른 프로그램만 쉽게 작성하게 하는 환경이 아니다.

**실수했을 때 이해할 수 있게 해주는 환경**이어야 한다.

그래서:

```text
expected initializer before ...

```

보다:

```text
Missing semicolon

    int x = 10
              ^

Add ';' here.

```

를 먼저 보여준다.

하지만 실제 compiler message도 `Show C++ Error`를 통해 볼 수 있게 한다.

학생이 성장하면 compiler의 실제 언어도 배울 수 있다.

---

## 17. Documentation should be executable

Small의 learner-facing API는 실제 example에 등장해야 한다.

> **Every learner-facing API should appear in an executable reference example.**

Reference examples는 documentation이다.

```text
reference/
    string.cpp
    array.cpp
    file.cpp
    drawing.cpp
    ...

```

그리고 실제 compile test를 통해 API와 documentation이 서로 어긋나지 않도록 한다.

---

## 18. Reference examples and fun programs serve different purposes

Reference example은:

> “이거 어떻게 쓰더라?”

에 답한다.

Program example은:

> “이걸로 뭘 만들 수 있지?”

에 답한다.

그래서:

```text
ASCII Art
Number Guessing
Drawing Pad
Bouncing Ball
Reaction Timer
Pong
Save Game

```

같은 프로그램은 API coverage보다 **재미와 이해 가능성**을 우선한다.

---

## 19. Reveal low-level concepts when they become exciting

Small은 low-level 개념을 영원히 숨기지 않는다.

Binary file I/O처럼 학생이:

> “내 게임의 save file을 만들 수 있네!”

라고 느끼는 순간에는 byte representation을 직접 경험하게 한다.

즉 low-level이라는 이유로 숨기는 것이 아니라:

> **지금 이 개념을 알면 더 재미있어지는가?**

를 기준으로 공개한다.

---

## 20. Keep the core small

Small core는 general-purpose programming vocabulary만 가진다.

```text
Values
    String
    Array

I/O
    Console
    File

Graphics / Input
    Window
    Keyboard
    Mouse

Time / Events
    StopWatch
    Timer

Sound

```

특정 분야 기능을 편리하다는 이유만으로 계속 core에 추가하지 않는다.

---

## 21. Extend outward, not inward

전문적인 교육 기능은 Extension으로 만든다.

```text
Extensions/
    Turtle
    Plot
    Image
    Physics
    Music
    Robot

```

따라서:

> **Small core teaches programming.**
> **
> Extensions teach things through programming.**

이라는 구조를 유지한다.

---

## 22. The beginner IDE must remain beginner-sized

현재 single-file Small IDE의 단순함은 기능 부족이 아니라 **의도적인 feature**다.

```text
New
Open
Save
Run
Stop

```

정도로 유지한다.

프로젝트가 필요해졌다고 현재 IDE에 project tree와 target configuration을 마구 붙이지 않는다.

---

## 23. Add another rung instead of making the first rung taller

학생이 성장하면 **Small Project**라는 다음 단계를 만든다.

```text
Small
    single file

       ↓

Small Project
    multiple files
    headers
    classes
    libraries

       ↓

Professional C++
    Qt Creator
    VS Code
    Visual Studio
    CMake

```

첫 번째 계단을 복잡하게 만드는 대신 **다음 계단을 추가한다.**

---

## 24. Toolchain complexity belongs to the environment developer, not the learner

이번 새 PC 설치 과정에서 특히 명확해진 원칙.

학생이:

```cpp
Print("Hello");

```

를 하기 위해:

```text
Qt version
Qt Creator
MinGW
MSVC
ARM64
x86-64
ABI
CMake
Ninja
Kit
Debugger
PATH

```

를 알아야 한다면 교육환경 설계가 실패한 것이다.

이 복잡성은 없어지는 것이 아니다.

**우리가 대신 책임진다.**

> **Toolchain complexity belongs to the environment developer, not the learner.**

---

## 25. Installation is part of the educational UX

따라서 one-click distribution은 단순한 편의 기능이 아니다.

최종 acceptance test는:

> 개발 도구가 하나도 없는 Windows PC에서
>
> `SmallCppSetup.exe` 하나를 실행한다.
>
> 설치한다.
>
> Small C++을 실행한다.
>
> 5분 안에 첫 프로그램을 Run한다.

이 과정에서 학생이:

```text
Qt
MinGW
CMake
Kit

```

이라는 단어를 한 번이라도 알아야 한다면 개선할 여지가 있다.

macOS에서도 같은 원칙을 적용한다.

---

## 26. Hide existing complexity; do not create new complexity to hide it

웹 이야기를 하면서 나온 원칙.

Small은 기존 C++ complexity를 숨기기 위해 **더 거대한 새로운 execution environment를 의무적으로 도입하지 않는다.**

예를 들어 단순한 native C++ 프로그램을 실행하기 위해 반드시:

```text
Browser
JavaScript engine
WASM runtime
Virtual filesystem
Web rendering abstraction

```

을 거쳐야 할 이유는 없다.

웹 기술 자체가 나쁘다는 뜻은 아니다.

Small의 목적에는 **native-first가 더 자연스럽다**는 뜻이다.

> **Hide unnecessary complexity; don't create new complexity just to hide the old one.**

---

## 27. Platform differences belong below the Small API

Windows와 macOS를 지원하더라도 학생 코드는 같아야 한다.

```cpp
Window window;
File file;
Timer timer;

```

안에:

```cpp
#ifdef _WIN32

```

같은 것이 학생에게 보이면 안 된다.

플랫폼 차이는 runtime/backend에서 처리한다.

Small의 learner-facing vocabulary는 플랫폼에 독립적이어야 한다.

---

## 28. Code should be beautiful enough to invite experimentation

Small의 API는 단지 짧기만 해서는 안 된다.

읽었을 때 의미가 보여야 한다.

그래서:

```cpp
PlaySound(Sound::Pop);
PlaySoundAndWait(Sound::Pop);

```

를:

```cpp
PlaySound(Sound::Pop, false);
PlaySound(Sound::Pop, true);

```

보다 선호한다.

코드가 설명서처럼 읽히는 것이 이상적이다.

학생이 코드를 보고:

> “이걸 조금 바꿔보고 싶다.”

고 느껴야 한다.

---

# Small C++의 세 가지 핵심 문장

지금까지의 철학을 세 문장으로 압축하면 여전히 이 세 개가 가장 좋다.

> **Small C++ is C++.**

> **Hide complexity until it becomes worth learning.**

> **Small should never teach something students later have to unlearn.**

> **Growing beyond Small is success; leaving Small is optional.**

그리고 이번에 네 번째를 추가할 만하다.

> **Toolchain complexity belongs to us, not to the learner.**

결국 Small C++은 **C++을 덜 가르치는 프로젝트가 아니라, C++을 올바른 순서로 가르치는 프로젝트**인 것 같아.

처음에는 아름답고 작은 부분만 보여주고, 학생이 성장하면서 그 뒤에 원래부터 존재했던 진짜 C++ 세계가 조금씩 드러나는 것. 그게 지금까지 우리가 계속 일관되게 선택해온 방향이야.
---

# Part II. Small as a Growing C++ Environment

초기의 교육 철학은 그대로 유지한다. 여기에 실제 구현과 Extension 설계를 진행하며 확립된 원칙을 추가한다.

## 29. Small is simple C++, not toy C++

Small은 첫 프로그램을 쉽게 만드는 환경이지만 교육용 장난감으로 끝나지 않는다.

> **Small is simple C++, not toy C++.**

처음에는 `SmallMain`과 작은 vocabulary로 시작하고, 필요해지면 `main`, namespace, standard library, multiple files, Small Extensions로 자연스럽게 성장한다. 처음부터 실제 C++이므로 프로그램이 커졌다는 이유로 배운 것을 버릴 필요가 없다.

---

## 30. Start small. Grow as far as you want.

> **Start small. Grow as far as you want.**

pure standard C++을 보여주는 이유는 Small을 버리게 하기 위해서가 아니라 Small 없이도 갈 수 있는 길이 열려 있음을 보여주기 위해서다.

```text
SmallMain
  ↓
main + Small
  ↓
ordinary C++ + Small API / Extensions
  ↓
larger multi-file programs
  ↓
another IDE or build system, if useful
```

어느 단계에서든 머물 수 있다.

---

## 31. Small IDE is the easiest way to use Small, not the only way

Small API와 Extensions는 일반 C++ library로 설계한다. Small IDE는 그것들을 가장 편하게 사용하는 환경이다.

다른 IDE로 옮기는 것과 Small을 떠나는 것은 같은 일이 아니다.

> **Moving to another IDE is not the same as leaving Small.**

---

## 32. Small IDE should remain the fastest place to try a C++ idea

Small IDE가 모든 규모에서 가장 강력한 IDE일 필요는 없다.

> **Small IDE should remain the fastest place to try a C++ idea.**

큰 프로젝트를 다른 환경에서 개발하는 숙련자도 Small IDE에서 몇 줄을 쓰고 Run을 눌러 API나 Extension을 즉시 실험할 수 있어야 한다.

`idea → type → Run → see result`는 beginner용 training wheel이 아니라 Small의 지속적인 가치다.

---

## 33. Classes represent things; free functions represent relationships

class의 member는 그 abstraction 자체에 본질적인 operation으로 제한한다.

`image.Width()`, `image.Save()`, `window.Open()`, `window.Show()`는 자연스러운 member다.

반면 Image와 Window처럼 독립적인 abstraction을 연결하는 operation은:

```cpp
DrawImage(window, image, x, y);
```

처럼 free function으로 둔다.

> **Classes represent things; free functions represent relationships between things.**

---

## 34. Extensions may depend on Core; Core never depends on Extensions

Extension은 Core를 사용할 수 있지만 Core는 Extension type을 알아서는 안 된다.

> **Extensions may depend on Core. Core never depends on Extensions.**

Image가 Window를 사용하는 것은 괜찮지만 Image가 생겼다는 이유로 Window에 `DrawImage()`를 추가하지 않는다. 기능이 늘어나도 Core는 작게 유지한다.

---

## 35. An extension is a self-contained folder

Extension은 설치 후에도 독립적인 ownership unit으로 유지한다.

```text
extensions/image/
    extension.json
    include/small/image.h
    lib/
    examples/
    tutorial/
```

사용자에게 보이는 API는 `#include <small/image.h>`처럼 단순하게 유지한다. Extension 폴더 하나를 추가하면 설치되고 제거하면 uninstall되는 mental model을 지향한다.

---

## 36. Install a capability, and Small should know how to teach it

Extension은 API와 binary뿐 아니라 executable examples와 tutorial도 함께 소유할 수 있다.

> **Install a capability, and Small also knows how to teach it.**

Core curriculum의 안정성을 유지하면서 Extension curriculum은 별도의 영역으로 확장한다.

---

## 37. Small owns it → Small automates it

Small이 직접 제공하고 책임지는 기능은 가능한 한 자동화한다. `#include <small/image.h>`를 사용하면 Small IDE가 include path와 linking을 처리한다.

반면 third-party library는 Small이 package manager가 되어 소유하지 않는다. 사용자가 설치한 외부 library를 사용할 수 있는 명확한 build path만 제공한다.

> **Small should automate what Small owns, and stay out of the way of what it doesn't.**

---

## 38. Add build complexity as another rung

single-file IDE의 단순함을 훼손하지 않는다. 여러 파일이 필요해질 때 `small.project` 같은 다음 build layer를 추가한다.

기본 사용자는 build system을 몰라도 되고, 필요해진 사용자는 build mode, include path, libraries, runtime files, compiler options, linker options를 점차 설정할 수 있다.

기존 원칙대로 첫 번째 계단을 높이는 대신 다음 계단을 추가한다.

---

## 39. Give common build intentions names; keep raw options as an escape hatch

일반적인 build 의도는 `quick`, `debug`, `release`처럼 의미 있는 preset으로 표현한다.

숙련자는 필요할 때 `compiler_options`, `linker_options` 같은 raw escape hatch를 사용할 수 있다.

Small이 compiler별 option을 번역할 수 있는 부분은 번역하고, 사용자가 직접 지정한 option은 사용자가 책임진다.

---

## 40. Keep repository ownership and public API organization separate

Extension의 물리적 구조는 ownership을 따르고 public include hierarchy는 사용자 경험을 따른다.

```text
extensions/image/include/small/image.h
```

에 파일이 있어도 사용자는:

```cpp
#include <small/image.h>
```

라고 쓴다.

> **Repository structure is for maintainers; public API structure is for users.**

---

# Small C++의 현재 핵심 문장

> **Small C++ is C++.**

> **Hide complexity until it becomes worth learning.**

> **Small should never teach something students later have to unlearn.**

> **Toolchain complexity belongs to us, not to the learner.**

> **Start small. Grow as far as you want.**

> **Small is simple C++, not toy C++.**

Small C++은 **C++을 덜 가르치는 프로젝트가 아니라, C++을 올바른 순서로 보여주고 불필요한 마찰을 줄이는 프로젝트**다.

처음에는 아름답고 작은 부분만 보여준다. 학생과 프로그램이 성장하면 그 뒤에 원래부터 존재했던 진짜 C++ 세계를 조금씩 드러낸다. 그리고 그 세계를 이해한 뒤에도 Small이 여전히 편하다면 계속 사용하면 된다.


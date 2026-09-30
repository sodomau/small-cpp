---
title: The Secret of SmallMain()
part: cpp
part-title: Part VI — Growing into C++
goal: SmallMain이 특별한 C++ 문법이 아니라 Small이 호출해 주던 함수였음을 이해하고 직접 main을 작성합니다.
related-example: reference/console
---

## `SmallMain()`의 비밀
처음부터 사용한 `SmallMain()`은 C++ 언어의 특별한 문법이 아닙니다. Small runtime이 여러분 대신 진짜 entry point를 준비하고, 필요한 초기화를 한 뒤 `SmallMain()`을 호출해 주었습니다.

개념적으로 그동안 뒤에서는 이런 일이 일어났습니다.

`main() → Small::InitializeSmall(argc, argv) → SmallMain() → Small::ShutdownSmall()`

이제 IDE는 여러분이 직접 top-level `main()`을 작성하면 숨겨진 entry point도, 자동 `small.h` include도, beginner namespace shortcut도 붙이지 않습니다. 따라서 Small을 계속 사용하려면 일반 library처럼 source에서 직접 `#include <small.h>`를 적습니다.

## 먼저 실행해 보세요

@code example1.cpp

## InitializeSmall은 Small 기능을 준비합니다
`#include <small.h>`는 compiler에게 Small의 type과 function 선언을 보여줍니다. 그리고 직접 `main()`을 쓸 때 Window, Sound 같은 runtime 기능을 사용하려면 `Small::InitializeSmall()`을 처음에 한 번 호출합니다.

프로그램이 끝나기 전에는 `Small::ShutdownSmall()`을 호출합니다. 이 함수는 Sound나 Window처럼 Small runtime이 관리하는 자원을 안전한 순서로 정리합니다. `SmallMain()`을 사용할 때는 숨겨진 entry point가 Initialize와 Shutdown을 모두 대신 호출했지만, 직접 `main()`을 쓰면 이 두 호출도 source에 명시합니다.

또 beginner mode가 끝났으므로 `Small::Print`, `Small::Window`, `Small::Black`처럼 `Small::` namespace도 직접 적습니다.

`return 0;`은 프로그램이 정상적으로 끝났다는 값을 운영체제에 돌려주는 전통적인 형태입니다. C++에서는 main 끝의 `return 0;`을 생략할 수도 있지만 여기서는 의미를 보여주기 위해 적습니다.

command-line argument를 사용하는 일반적인 main 형태도 그대로 지원합니다.

## 다음 단계

@code example2.cpp

## 이제 source가 스스로 필요한 것을 말합니다
`SmallMain()` 시절에는 IDE가 `small.h`와 beginner namespace shortcut을 자동으로 준비했습니다. 이제 `main()` 프로그램은 ordinary C++ source처럼 자신이 사용하는 Small library를 직접 include하고 namespace를 명시합니다.

Small IDE에 별도의 “Standard C++ mode” 버튼은 없습니다. top-level `main()`을 작성하는 것 자체가 이 경계를 만듭니다.

Small API를 하나도 사용하지 않는다면 `#include <small.h>`도 `Small::InitializeSmall()`도 필요 없습니다. 마지막 lesson에서 바로 그런 프로그램을 작성합니다.

## Exercise — main으로 옮기기

`SmallMain` Hello 프로그램을 진짜 `main()`으로 바꾸세요. `#include <small.h>`를 직접 적고 `Small::InitializeSmall()`, `Small::Print`, `Small::ShutdownSmall()`을 사용하세요.

@exercise exercise1_starter.cpp

### Hint

함수 이름을 main으로 바꾸는 것만이 아니라 return type을 `int`로 하고 끝나기 전에 `Small::ShutdownSmall();`을 호출한 뒤 `return 0;`을 적어 보세요.

@solution exercise1_solution.cpp

## Exercise — argc와 argv 넘기기

`#include <small.h>`와 `int main(int argc, char* argv[])`를 작성하고 argc, argv를 `Small::InitializeSmall`에 전달한 뒤 argc를 출력하고 프로그램을 끝내기 전에 `Small::ShutdownSmall()`을 호출하세요.

@exercise exercise2_starter.cpp

### Hint

`Small::InitializeSmall(argc, argv);` 다음에 `Small::Print("argc: ", argc);`를 사용하고 `return 0;` 전에 `Small::ShutdownSmall();`을 호출하세요.

@solution exercise2_solution.cpp

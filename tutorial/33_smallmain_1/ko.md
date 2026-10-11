---
title: 프로그램의 시작점 이해하기
part: cpp
part-title: 작은 걸음 VI — C++로 성장하기
goal: 프로그램의 시작점 이해하기
related-example: reference/console
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 진짜 시작 함수 main 쓰기

### 이번에 배울 것

**main**은 C++ 프로그램의 시작 함수입니다. 지금까지는 Small이 준비한 main이 small_main을 호출했습니다. 이제 준비와 종료까지 직접 적습니다.

### 실행해 보기

@code example1.cpp

이 IDE에서 직접 main을 쓰면 자동 헤더·이름 공간 지원도 끝납니다. 그래서 small.h를 포함하고 Small::를 씁니다.

initialize_small → 내 작업 → shutdown_small 순서입니다. return 0은 정상 종료를 나타냅니다. Hello from main!이 출력되는지 확인하세요.

## 창을 정리한 뒤 런타임 끝내기

### 이번에 배울 것

**런타임**은 창·소리 같은 실행 기능을 지원하는 기반입니다. 그 기능을 쓰는 객체를 먼저 정리한 뒤 기반을 종료해야 합니다.

### 실행해 보기

@code smallmain_2_example2.cpp

안쪽 중괄호 범위가 끝나면 Window 객체가 정리됩니다. 그 뒤 shutdown_small을 호출합니다. 창을 닫는 것과 객체 수명이 끝나는 것은 다릅니다.

argc와 argv는 명령줄로 전달된 정보를 받는 형태입니다. 이번은 선택 심화입니다. 포인터 표기를 지금 모두 외울 필요는 없습니다.

## Exercise — main으로 옮기기

`small_main` Hello 프로그램을 진짜 `main()`으로 바꾸세요. `#include <small.h>`를 직접 적고 `Small::initialize_small()`, `Small::print`, `Small::shutdown_small()`을 사용하세요.

@exercise exercise1_starter.cpp

### Hint

함수 이름을 main으로 바꾸는 것만이 아니라 return type을 `int`로 하고 끝나기 전에 `Small::shutdown_small();`을 호출한 뒤 `return 0;`을 적어 보세요.

@solution exercise1_solution.cpp

## 더 해 보기 (선택)

## Exercise — argc와 argv 넘기기

`#include <small.h>`와 `int main(int argc, char* argv[])`를 작성하고 argc, argv를 `Small::initialize_small`에 전달한 뒤 argc를 출력하고 프로그램을 끝내기 전에 `Small::shutdown_small()`을 호출하세요.

@exercise smallmain_2_exercise2_starter.cpp

### Hint

`Small::initialize_small(argc, argv);` 다음에 `Small::print("argc: ", argc);`를 사용하고 `return 0;` 전에 `Small::shutdown_small();`을 호출하세요.

@solution smallmain_2_exercise2_solution.cpp

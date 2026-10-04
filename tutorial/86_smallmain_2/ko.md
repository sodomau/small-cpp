---
title: 창을 정리한 뒤 런타임 끝내기
part: cpp
part-title: 작은 걸음 VI — C++로 성장하기
goal: 창을 정리한 뒤 런타임 끝내기
related-example: reference/console
---

## 이번에 배울 것

**런타임**은 창·소리 같은 실행 기능을 지원하는 기반입니다. 그 기능을 쓰는 객체를 먼저 정리한 뒤 기반을 종료해야 합니다.

## 실행해 보기

@code example2.cpp

안쪽 중괄호 범위가 끝나면 Window 객체가 정리됩니다. 그 뒤 shutdown_small을 호출합니다. 창을 닫는 것과 객체 수명이 끝나는 것은 다릅니다.

argc와 argv는 명령줄로 전달된 정보를 받는 형태입니다. 이번은 선택 심화입니다. 포인터 표기를 지금 모두 외울 필요는 없습니다.

## Exercise — argc와 argv 넘기기

`#include <small.h>`와 `int main(int argc, char* argv[])`를 작성하고 argc, argv를 `Small::initialize_small`에 전달한 뒤 argc를 출력하고 프로그램을 끝내기 전에 `Small::shutdown_small()`을 호출하세요.

@exercise exercise2_starter.cpp

### Hint

`Small::initialize_small(argc, argv);` 다음에 `Small::print("argc: ", argc);`를 사용하고 `return 0;` 전에 `Small::shutdown_small();`을 호출하세요.

@solution exercise2_solution.cpp

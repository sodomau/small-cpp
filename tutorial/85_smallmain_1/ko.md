---
title: 진짜 시작 함수 main 쓰기
part: cpp
part-title: 작은 걸음 VI — C++로 성장하기
goal: 진짜 시작 함수 main 쓰기
related-example: reference/console
---

## 이번에 배울 것

**main**은 C++ 프로그램의 시작 함수입니다. 지금까지는 Small이 준비한 main이 small_main을 호출했습니다. 이제 준비와 종료까지 직접 적습니다.

## 실행해 보기

@code example1.cpp

이 IDE에서 직접 main을 쓰면 자동 헤더·이름 공간 지원도 끝납니다. 그래서 small.h를 포함하고 Small::를 씁니다.

initialize_small → 내 작업 → shutdown_small 순서입니다. return 0은 정상 종료를 나타냅니다. Hello from main!이 출력되는지 확인하세요.

## Exercise — main으로 옮기기

`small_main` Hello 프로그램을 진짜 `main()`으로 바꾸세요. `#include <small.h>`를 직접 적고 `Small::initialize_small()`, `Small::print`, `Small::shutdown_small()`을 사용하세요.

@exercise exercise1_starter.cpp

### Hint

함수 이름을 main으로 바꾸는 것만이 아니라 return type을 `int`로 하고 끝나기 전에 `Small::shutdown_small();`을 호출한 뒤 `return 0;`을 적어 보세요.

@solution exercise1_solution.cpp


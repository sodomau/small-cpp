---
title: Small 없이 인사하기
part: cpp
part-title: 작은 걸음 VI — C++로 성장하기
goal: Small 없이 인사하기
related-example: reference/console
---

## 이번에 배울 것

이미 배운 표준 도구만 사용하면 Small 없이도 같은 일을 할 수 있습니다.

## 실행해 보기

@code example1.cpp

small_main 대신 main, String 대신 std::string, `input` 대신 getline, `print` 대신 cout을 씁니다. Alex를 입력하면 Hello, Alex가 나옵니다.

Small 기능을 쓰지 않으므로 small.h나 initialize_small, shutdown_small도 필요 없습니다.

## Exercise — Small 없는 합계

Small API 없이 `std::vector<int>`의 값을 모두 더해 `std::cout`으로 출력하는 main 프로그램을 작성하세요.

@exercise exercise1_starter.cpp

### Hint

`#include <iostream>`과 `#include <vector>`를 직접 적으세요.

@solution exercise1_solution.cpp


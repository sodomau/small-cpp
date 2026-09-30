---
title: Meet the Standard Library
part: cpp
part-title: Part VI — Growing into C++
goal: Small이 제공하던 편리한 기능 뒤에 C++ Standard Library가 있다는 것을 만나고 몇 가지 표준 함수를 사용합니다.
related-example: reference/console
---

## Small 밖에도 이미 많은 도구가 있습니다
우리는 지금까지 `Print`, `String`, `Array`처럼 Small이 준비한 이름을 사용했습니다. 하지만 C++ 자체의 생태계에는 모든 표준 C++ 환경에서 사용할 수 있는 **Standard Library**가 있습니다.

Small도 C++ 위에 만들어졌기 때문에 그 도구들을 함께 사용할 수 있습니다. 이제부터 Small이 숨겨주던 부분을 하나씩 직접 만나 봅니다.

## 먼저 실행해 보세요

@code example1.cpp

## `std::`는 표준 라이브러리의 이름표
`std::min`의 `std::`는 이 이름이 C++ Standard Library의 `std` namespace 안에 있다는 뜻입니다. namespace는 같은 이름들이 서로 충돌하지 않도록 묶어 주는 방법입니다.

Small에서는 beginner mode가 `Small::`을 숨겨주었지만, 표준 라이브러리는 여기서부터 `std::`를 직접 써 봅니다.

표준 라이브러리는 매우 크므로 전부 외우는 것이 목표가 아닙니다. 필요한 기능이 이미 있는지 찾아보고 사용할 수 있다는 사실을 아는 것이 중요합니다.

## 조금 더 C++답게

@code example2.cpp

## Small을 버리는 lesson이 아닙니다
지금은 Small과 Standard Library를 같은 프로그램에서 함께 사용합니다. 익숙한 환경을 유지하면서 C++의 실제 이름과 도구를 조금씩 늘려 가는 단계입니다.

다음에는 Small의 `String`과 `Array`에 대응하는 표준 C++ type을 직접 사용해 봅니다.

## Exercise — min과 max

두 int 17과 42에 대해 `std::min`과 `std::max`를 사용해 작은 값과 큰 값을 출력하세요.

@exercise exercise1_starter.cpp

### Hint

`Print(std::min(17, 42));`처럼 표준 함수를 Print 안에서도 바로 사용할 수 있습니다.

@solution exercise1_solution.cpp

## Exercise — 절댓값

-25의 절댓값을 `std::abs`로 구해 출력하세요.

@exercise exercise2_starter.cpp

### Hint

`std::abs(-25)`의 결과는 int 25입니다.

@solution exercise2_solution.cpp

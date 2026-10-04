---
title: 이미 만들어진 도구 사용하기
part: cpp
part-title: 작은 걸음 VI — C++로 성장하기
goal: 이미 만들어진 도구 사용하기
related-example: reference/console
---

## 이번에 배울 것

**라이브러리**는 프로그램에서 쓸 수 있도록 만든 도구들의 모음입니다. C++ 표준 라이브러리는 여러 환경에서 공통으로 사용하는 도구를 제공합니다.

## 실행해 보기

@code example1.cpp

std::min은 두 값 중 작은 값, std::max는 큰 값을 돌려줍니다. 예상 출력은 Min: 3, Max: 12입니다.

std::는 표준 라이브러리에 속한 이름이라는 표시입니다. 지금은 Small IDE가 필요한 기본 헤더를 준비해 줍니다.

## Exercise — min과 max

두 int 17과 42에 대해 `std::min`과 `std::max`를 사용해 작은 값과 큰 값을 출력하세요.

@exercise exercise1_starter.cpp

### Hint

`print(std::min(17, 42));`처럼 표준 함수를 `print` 안에서도 바로 사용할 수 있습니다.

@solution exercise1_solution.cpp


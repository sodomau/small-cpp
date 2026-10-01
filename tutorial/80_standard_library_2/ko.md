---
title: 음수의 크기 구하기
part: cpp
part-title: Part VI — C++로 성장하기
goal: 음수의 크기 구하기
related-example: reference/console
---

## 이번에 배울 것

**절댓값**은 수직선에서 0까지의 거리입니다. std::abs로 구합니다.

## 실행해 보기

@code example2.cpp

-12의 절댓값은 12입니다. 예상 출력은 Absolute: 12, Smaller: -12입니다.

함수의 이름과 입력·결과를 알면 내부 구현을 다시 만들지 않고 사용할 수 있습니다. 값의 범위에는 한계가 있으므로 여기서는 작은 정수로 연습합니다.

## Exercise — 절댓값

-25의 절댓값을 `std::abs`로 구해 출력하세요.

@exercise exercise2_starter.cpp

### Hint

`std::abs(-25)`의 결과는 int 25입니다.

@solution exercise2_solution.cpp

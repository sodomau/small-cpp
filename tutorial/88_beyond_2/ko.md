---
title: 표준 C++에서도 같은 절차 쓰기
part: cpp
part-title: Part VI — Growing into C++
goal: 표준 C++에서도 같은 절차 쓰기
related-example: reference/console
---

## 이번에 배울 것

도구의 표기가 바뀌어도 **값을 저장하고 반복하며 합산하는 절차**는 그대로입니다.

## 실행해 보기

@code example2.cpp

vector의 값을 범위 기반 for로 더하고, 함수가 돌려준 값을 cout으로 출력합니다. 결과는 Sum: 25입니다.

지금까지의 변수·조건·반복·함수는 모두 일반 C++에서도 사용됩니다. 이후에는 만들고 싶은 것에 필요한 도구를 조금씩 더 배우면 됩니다.

## Exercise — 첫 standard C++ 함수

`const std::string&`을 받아 `Hello, 이름!`을 std::cout으로 출력하는 `Greet` 함수를 만들고 main에서 호출하세요.

@exercise exercise2_starter.cpp

### Hint

`#include <iostream>`과 `#include <string>`이 필요합니다.

@solution exercise2_solution.cpp

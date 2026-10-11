---
title: Small 없이 C++ 프로그램 만들기
part: cpp
part-title: 작은 걸음 VI — C++로 성장하기
goal: Small 없이 C++ 프로그램 만들기
related-example: reference/console
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## Small 없이 인사하기

### 이번에 배울 것

이미 배운 표준 도구만 사용하면 Small 없이도 같은 일을 할 수 있습니다.

### 실행해 보기

@code example1.cpp

small_main 대신 main, String 대신 std::string, `input` 대신 getline, `print` 대신 cout을 씁니다. Alex를 입력하면 Hello, Alex가 나옵니다.

Small 기능을 쓰지 않으므로 small.h나 initialize_small, shutdown_small도 필요 없습니다.

## 표준 C++에서도 같은 절차 쓰기

### 이번에 배울 것

도구의 표기가 바뀌어도 **값을 저장하고 반복하며 합산하는 절차**는 그대로입니다.

### 실행해 보기

@code beyond_2_example2.cpp

vector의 값을 범위 기반 for로 더하고, 함수가 돌려준 값을 cout으로 출력합니다. 결과는 Sum: 25입니다.

지금까지의 변수·조건·반복·함수는 모두 일반 C++에서도 사용됩니다. 이후에는 만들고 싶은 것에 필요한 도구를 조금씩 더 배우면 됩니다.

## Exercise — Small 없는 합계

Small API 없이 `std::vector<int>`의 값을 모두 더해 `std::cout`으로 출력하는 main 프로그램을 작성하세요.

@exercise exercise1_starter.cpp

### Hint

`#include <iostream>`과 `#include <vector>`를 직접 적으세요.

@solution exercise1_solution.cpp

## 더 해 보기 (선택)

## Exercise — 첫 standard C++ 함수

`const std::string&`을 받아 `Hello, 이름!`을 std::cout으로 출력하는 `greet` 함수를 만들고 main에서 호출하세요.

@exercise beyond_2_exercise2_starter.cpp

### Hint

`#include <iostream>`과 `#include <string>`이 필요합니다.

@solution beyond_2_exercise2_solution.cpp

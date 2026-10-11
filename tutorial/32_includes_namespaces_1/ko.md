---
title: 헤더와 네임스페이스 이해하기
part: cpp
part-title: 작은 걸음 VI — C++로 성장하기
goal: 헤더와 네임스페이스 이해하기
related-example: reference/console
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 필요한 도구를 코드에 적기

### 이번에 배울 것

**헤더**는 다른 코드의 도구를 사용할 수 있도록 선언을 알려 주는 파일입니다. #include는 그 헤더를 포함하는 지시문입니다.

### 실행해 보기

@code example1.cpp

iostream은 표준 입출력, string은 std::string을 위해 포함합니다. std::cout << 값은 출력, std::getline(std::cin, name)은 한 줄 입력입니다. Alex를 넣으면 Hello, Alex가 나옵니다.

이번에는 small_main을 유지하며 입출력 도구만 바꿉니다.

## 어디에 속한 이름인지 표시하기

### 이번에 배울 것

**이름 공간(namespace)**은 이름들을 묶어 구별하는 영역입니다. ::로 어느 영역의 이름인지 표시합니다.

### 실행해 보기

@code includes_namespaces_2_example2.cpp

Small::print와 std::cout은 서로 다른 도구입니다. 예제는 Small namespace와 Standard namespace를 차례로 출력합니다.

이름 공간은 객체가 아닙니다. window.show()의 점과 Small::print의 ::를 구분하세요.

## Exercise — std::cout 사용하기

`#include <iostream>`을 적고 `std::cout`으로 `Hello C++`과 줄바꿈을 출력하세요. `small_main()`은 아직 그대로 사용합니다.

@exercise exercise1_starter.cpp

### Hint

`std::cout << "Hello C++" << "\n";`처럼 값을 output stream으로 보낼 수 있습니다.

@solution exercise1_solution.cpp

## 더 해 보기 (선택)

## Exercise — 표준 입출력으로 이름 읽기

`std::string name`을 만들고 `std::getline(std::cin, name)`으로 한 줄을 입력받아 `std::cout`으로 다시 출력하세요.

@exercise includes_namespaces_2_exercise2_starter.cpp

### Hint

`<iostream>`과 `<string>`을 include하고, 먼저 prompt를 cout으로 출력한 뒤 getline을 호출하세요.

@solution includes_namespaces_2_exercise2_solution.cpp

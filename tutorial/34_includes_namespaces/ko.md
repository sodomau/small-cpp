---
title: #include and Namespaces
part: cpp
part-title: Part VI — Growing into C++
goal: #include와 namespace가 이름과 라이브러리 기능을 프로그램에 어떻게 가져오는지 이해합니다.
related-example: reference/console
---

## 지금까지 보이지 않던 첫 줄
Small IDE는 `SmallMain()` 프로그램을 compile할 때 `small.h`를 자동으로 포함해 주었습니다. 그래서 처음부터 `#include`를 쓰지 않고 프로그램의 핵심에 집중할 수 있었습니다.

일반 C++에서는 사용하는 library의 header를 source에 직접 적습니다. 이제 `#include <iostream>`과 `#include <string>`을 직접 쓰고, 표준 console 입출력도 만나 봅시다.

## 먼저 실행해 보세요

@code example1.cpp

## header, namespace, 그리고 stream
`#include <iostream>`은 표준 console 입출력인 `std::cout`과 `std::cin`을 사용할 수 있게 합니다. `#include <string>`은 `std::string`을 위한 header입니다.

`std::cout`은 **standard output stream**입니다. `<<` 뒤의 값을 왼쪽에서 오른쪽으로 출력 stream에 보냅니다. `"\n"`은 줄바꿈 문자입니다.

`std::cin`은 **standard input stream**입니다. `std::getline(std::cin, name)`은 입력에서 한 줄을 읽어 `name`에 저장합니다.

여기서 `std::`는 Standard Library의 `std` namespace 안의 이름이라는 뜻입니다. stream의 내부 구조나 `<<` 연산자의 구현을 지금 알 필요는 없습니다. Small의 `Print`와 `Input`이 하던 일을 표준 C++에서는 어떤 표면으로 만나는지만 익히면 됩니다.

## 조금 더 C++답게

@code example2.cpp

## 이제 마지막으로 entry point를 바꿉니다
이 lesson에서는 `#include`, `std::cout`, `std::cin`, `std::getline`, `std::string`, namespace를 직접 사용했습니다. 아직 프로그램의 시작만 `SmallMain()`이었습니다.

다음 lesson에서는 `SmallMain()`의 비밀을 열고 진짜 C++ entry point인 `main()`을 직접 작성합니다. 그 순간부터 Small도 특별한 내장 기능이 아니라 **명시적으로 include해서 사용하는 C++ library**가 됩니다.

## Exercise — std::cout 사용하기

`#include <iostream>`을 적고 `std::cout`으로 `Hello C++`과 줄바꿈을 출력하세요. `SmallMain()`은 아직 그대로 사용합니다.

@exercise exercise1_starter.cpp

### Hint

`std::cout << "Hello C++" << "\\n";`처럼 값을 output stream으로 보낼 수 있습니다.

@solution exercise1_solution.cpp

## Exercise — Small namespace 직접 쓰기

`std::string name`을 만들고 `std::getline(std::cin, name)`으로 한 줄을 입력받아 `std::cout`으로 다시 출력하세요.

@exercise exercise2_starter.cpp

### Hint

`<iostream>`과 `<string>`을 include하고, 먼저 prompt를 cout으로 출력한 뒤 getline을 호출하세요.

@solution exercise2_solution.cpp

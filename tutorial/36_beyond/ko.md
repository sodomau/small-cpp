---
title: You Already Know C++
part: cpp
part-title: Part VI — Growing into C++
goal: Small 없이 표준 C++ main 프로그램을 작성하고 지금까지 배운 개념이 그대로 이어짐을 확인합니다.
related-example: reference/console
---

## 이제 Small 없이도 시작할 수 있습니다
마지막 프로그램에는 새로운 핵심 개념이 없습니다. Lesson 34에서 이미 사용한 `#include <iostream>`, `std::string`, `std::cout`, `std::cin`, `std::getline`을 그대로 사용합니다.

달라지는 것은 딱 하나입니다. Lesson 35에서 배운 진짜 `main()`을 entry point로 사용하고, Small을 전혀 include하지 않습니다.

## 먼저 실행해 보세요

@code example1.cpp

## 이미 본 조각들이 하나의 일반 C++ 프로그램이 됩니다
Lesson 34에서는 같은 표준 입출력 코드를 `SmallMain()` 안에서 사용했습니다. 이제 `SmallMain()`이 `main()`으로 바뀌었고 Small이 사라졌을 뿐입니다.

Small의 `Print` 대신 `std::cout`, `Input` 대신 `std::getline`과 `std::cin`, `String` 대신 `std::string`을 사용합니다. 이 이름과 사용법은 앞 lesson에서 이미 만났습니다.

따라서 마지막 프로그램은 갑자기 새로운 C++를 배우는 예제가 아니라, **지금까지 배운 조각만으로 ordinary C++ source가 완성된다는 확인**입니다.

## 다음 단계

@code example2.cpp

## 여기서 끝이 아니라 다음 단계의 시작
이제 여러 source file과 header를 사용하는 프로젝트, 더 큰 Standard Library, debugging, 다른 library 사용법을 배울 준비가 되었습니다.

Small IDE는 single-file 프로그램을 빠르게 실험하는 도구로 계속 사용할 수 있습니다. 더 큰 프로그램을 만들고 싶어질 때는 우리가 계획한 **Small Project** 같은 중간 단계나 일반 개발 IDE로 넘어가면 됩니다.

중요한 것은 Small에서 별도의 언어를 배운 것이 아니라는 점입니다. 처음부터 C++의 변수, 함수, loop, object와 memory model을 사용했고, 마지막에 그 주변의 편의를 하나씩 걷어냈습니다.

## Exercise — Small 없는 합계

Small API 없이 `std::vector<int>`의 값을 모두 더해 `std::cout`으로 출력하는 main 프로그램을 작성하세요.

@exercise exercise1_starter.cpp

### Hint

`#include <iostream>`과 `#include <vector>`를 직접 적으세요.

@solution exercise1_solution.cpp

## Exercise — 첫 standard C++ 함수

`const std::string&`을 받아 `Hello, 이름!`을 std::cout으로 출력하는 `Greet` 함수를 만들고 main에서 호출하세요.

@exercise exercise2_starter.cpp

### Hint

`#include <iostream>`과 `#include <string>`이 필요합니다.

@solution exercise2_solution.cpp

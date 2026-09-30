---
title: std::string and std::vector
part: cpp
part-title: Part VI — Growing into C++
goal: Small의 String과 Array에 대응하는 std::string과 std::vector를 직접 사용합니다.
related-example: reference/console
---

## 익숙한 개념에 새로운 이름 붙이기
Small의 `String`과 `Array`는 처음 배우기 편하도록 만든 type입니다. 표준 C++에서는 문자열에 `std::string`, 크기가 변하는 연속된 값 모음에 `std::vector`를 많이 사용합니다.

개념은 이미 알고 있습니다. 이름과 몇 가지 member function이 달라질 뿐입니다.

Small의 `String`은 `std::string`으로부터 만들 수 있도록 연결되어 있어서 두 세계를 단계적으로 섞어 쓸 수도 있습니다. 하지만 이 lesson의 목적은 표준 type 자체의 이름과 사용법에 익숙해지는 것입니다.

## 먼저 실행해 보세요

@code example1.cpp

## Length()는 size()로
Small에서는 `text.Length()`와 `numbers.Length()`로 길이를 확인했습니다. 표준 `std::string`과 `std::vector`에서는 `size()`를 사용합니다.

여기에는 한 가지 차이도 있습니다. Small의 `Array`는 처음 만들 때 길이나 값들을 정하고, 그 뒤에는 길이를 바꾸는 기능을 일부러 제공하지 않습니다. 반면 `std::vector`는 크기가 변할 수 있는 container라서 `push_back()`으로 끝에 새 값을 추가할 수 있습니다.

문법과 기능의 범위는 조금 달라도 “object에게 member function을 호출한다”는 개념은 이미 class lesson에서 배웠습니다.

Lesson 31 이후이므로 큰 표준 object를 읽기만 하는 함수에는 `const std::vector<int>&` 같은 일반적인 C++ style도 자연스럽게 사용할 수 있습니다.

## 조금 더 C++답게

@code example2.cpp

## 새로운 문법보다 이미 아는 개념을 보세요
`std::vector<int>`도 여러 int를 순서대로 저장하고 index로 접근합니다. `std::string`도 여러 문자를 저장합니다. Small에서 배운 loop, search, sorting 아이디어는 그대로 적용됩니다.

예제의 `for (int value : numbers)`는 container의 모든 값을 차례로 보는 C++의 **range-based for**입니다. 기존 index for를 계속 사용해도 됩니다.

## Exercise — vector에 값 추가

`std::vector<int>`에 5, 10을 넣어 만들고 `push_back(15)`로 하나 더 추가한 뒤 모두 출력하세요.

@exercise exercise1_starter.cpp

### Hint

range-based for를 쓰면 `for (int value : numbers)`로 모든 값을 볼 수 있습니다.

@solution exercise1_solution.cpp

## Exercise — std::string 함수

`const std::string&`을 받아 길이를 돌려주는 `TextLength` 함수를 만들고 "Small"의 길이를 출력하세요.

@exercise exercise2_starter.cpp

### Hint

`text.size()`는 표준 C++의 unsigned 크기 type을 돌려줍니다. 이 연습의 return type은 int이므로 `static_cast<int>(text.size())`로 명시적으로 바꾸어 반환하세요.

@solution exercise2_solution.cpp

---
title: 어디에 속한 이름인지 표시하기
part: cpp
part-title: Part VI — C++로 성장하기
goal: 어디에 속한 이름인지 표시하기
related-example: reference/console
---

## 이번에 배울 것

**이름 공간(namespace)**은 이름들을 묶어 구별하는 영역입니다. ::로 어느 영역의 이름인지 표시합니다.

## 실행해 보기

@code example2.cpp

Small::Print와 std::cout은 서로 다른 도구입니다. 예제는 Small namespace와 Standard namespace를 차례로 출력합니다.

이름 공간은 객체가 아닙니다. window.Show()의 점과 Small::Print의 ::를 구분하세요.

## Exercise — 표준 입출력으로 이름 읽기

`std::string name`을 만들고 `std::getline(std::cin, name)`으로 한 줄을 입력받아 `std::cout`으로 다시 출력하세요.

@exercise exercise2_starter.cpp

### Hint

`<iostream>`과 `<string>`을 include하고, 먼저 prompt를 cout으로 출력한 뒤 getline을 호출하세요.

@solution exercise2_solution.cpp

---
title: 관련된 값 묶기
part: types
part-title: Part V — Making Your Own Types
goal: 관련된 값 묶기
related-example: reference/array
---

## 이번에 배울 것

**struct**는 관련된 값들을 묶는 새 타입을 정의합니다. Player 하나에 이름과 점수를 함께 담아 봅니다.

## 실행해 보기

@code example1.cpp

String과 int가 이미 있던 타입이라면 Player는 우리가 만든 타입입니다. player.name처럼 점으로 안의 값에 접근합니다.

예제는 Alex: 1200을 출력합니다. struct 정의의 닫는 중괄호 뒤에는 ;이 필요합니다.

## Exercise — Point 만들기

x와 y를 double로 가지는 `Point` struct를 만들고 (3.5, 7.0)을 저장해 출력하세요.

@exercise exercise1_starter.cpp

### Hint

`struct Point { double x; double y; };`로 시작하세요.

@solution exercise1_solution.cpp


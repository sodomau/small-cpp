---
title: 구조체로 관련된 값 묶기
part: types
part-title: 작은 걸음 V — 나만의 자료형 만들기
goal: 구조체로 관련된 값 묶기
related-example: reference/array
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 관련된 값 묶기

### 이번에 배울 것

**struct**는 관련된 값들을 묶는 새 타입을 정의합니다. Player 하나에 이름과 점수를 함께 담아 봅니다.

### 실행해 보기

@code example1.cpp

String과 int가 이미 있던 타입이라면 Player는 우리가 만든 타입입니다. player.name처럼 점으로 안의 값에 접근합니다.

예제는 Alex: 1200을 출력합니다. struct 정의의 닫는 중괄호 뒤에는 ;이 필요합니다.

## 묶은 값을 여러 개 담기

### 이번에 배울 것

직접 만든 타입도 배열의 원소가 될 수 있습니다. Array<Player>는 여러 선수의 정보를 담습니다.

### 실행해 보기

@code struct_2_example2.cpp

players[i].score는 i번째 선수의 점수입니다. 최댓값 위치를 찾던 방법을 그대로 쓰고, 마지막에는 그 선수의 이름을 출력합니다.

예상 결과는 Winner: Mina입니다. 점수를 바꾸어 우승자가 달라지는지 보세요.

## Exercise — Point 만들기

x와 y를 double로 가지는 `Point` struct를 만들고 (3.5, 7.0)을 저장해 출력하세요.

@exercise exercise1_starter.cpp

### Hint

`struct Point { double x; double y; };`로 시작하세요.

@solution exercise1_solution.cpp

## 더 해 보기 (선택)

## Exercise — 최고 점수 찾기

name과 score를 가진 Player 세 명을 Array에 넣고 가장 높은 score의 Player 이름을 출력하세요.

@exercise struct_2_exercise2_starter.cpp

### Hint

Lesson의 best index 패턴을 사용하세요.

@solution struct_2_exercise2_solution.cpp

---
title: 묶은 값을 여러 개 담기
part: types
part-title: Part V — Making Your Own Types
goal: 묶은 값을 여러 개 담기
related-example: reference/array
---

## 이번에 배울 것

직접 만든 타입도 배열의 원소가 될 수 있습니다. Array<Player>는 여러 선수의 정보를 담습니다.

## 실행해 보기

@code example2.cpp

players[i].score는 i번째 선수의 점수입니다. 최댓값 위치를 찾던 방법을 그대로 쓰고, 마지막에는 그 선수의 이름을 출력합니다.

예상 결과는 Winner: Mina입니다. 점수를 바꾸어 우승자가 달라지는지 보세요.

## Exercise — 최고 점수 찾기

name과 score를 가진 Player 세 명을 Array에 넣고 가장 높은 score의 Player 이름을 출력하세요.

@exercise exercise2_starter.cpp

### Hint

Lesson의 best index 패턴을 사용하세요.

@solution exercise2_solution.cpp

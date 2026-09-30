---
title: struct — Make Your Own Value
part: types
part-title: Part V — Making Your Own Types
goal: 여러 값을 하나의 의미 있는 새 type으로 묶어 사용합니다.
related-example: reference/array
---

## 서로 관련된 값을 하나로 묶기
게임의 player에는 x, y, score처럼 함께 다니는 값이 많습니다. 변수를 따로 만들 수도 있지만, 이 값들이 **한 명의 Player**에 속한다는 사실을 코드에 표현하면 더 이해하기 쉽습니다.

`struct`를 사용하면 내가 직접 새로운 type을 만들 수 있습니다.

## 먼저 실행해 보세요

@code example1.cpp

## struct도 하나의 값입니다
`Player player;`는 우리가 만든 Player type의 값을 하나 만듭니다. 점을 사용해 `player.name`, `player.score`처럼 안의 값을 사용합니다.

Array의 element type도 내가 만든 struct가 될 수 있습니다. 그러면 여러 player를 하나의 Array에 모아 알고리즘을 적용할 수 있습니다.

## 조금 바꾸어 보기

@code example2.cpp

## type은 프로그램의 생각을 표현합니다
`int x`, `int y`, `int score`만 보면 이 값들이 무엇을 이루는지 사람이 추측해야 합니다. `Player`, `Point`, `Enemy` 같은 type을 만들면 프로그램이 다루는 개념 자체를 코드에 넣을 수 있습니다.

다음 lesson에서는 data뿐 아니라 그 data가 할 수 있는 **behavior**도 같은 type 안에 넣습니다.

## Exercise — Point 만들기

x와 y를 double로 가지는 `Point` struct를 만들고 (3.5, 7.0)을 저장해 출력하세요.

@exercise exercise1_starter.cpp

### Hint

`struct Point { double x; double y; };`로 시작하세요.

@solution exercise1_solution.cpp

## Exercise — 최고 점수 찾기

name과 score를 가진 Player 세 명을 Array에 넣고 가장 높은 score의 Player 이름을 출력하세요.

@exercise exercise2_starter.cpp

### Hint

Lesson의 best index 패턴을 사용하세요.

@solution exercise2_solution.cpp

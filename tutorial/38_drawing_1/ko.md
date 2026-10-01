---
title: 좌표로 그림 그리기
part: making_things
part-title: 작은 걸음 II — 만들며 배우기
goal: 좌표로 그림 그리기
related-example: reference/drawing
---

## 이번에 배울 것

**좌표**는 화면의 위치를 숫자로 나타낸 것입니다. 창의 왼쪽 위가 (0, 0)이고 x는 오른쪽, y는 아래쪽으로 커집니다.

## 실행해 보기

@code example1.cpp

Clear는 배경을 지웁니다. `FillCircle(320, 240, 80, Yellow)`는 중심 (320, 240), 반지름 80인 노란 원을 채웁니다. DrawCircle은 테두리만 그립니다.

DrawLine의 네 숫자는 시작점 x, y와 끝점 x, y입니다. 나중에 그린 것이 먼저 그린 것을 덮습니다. 노란 얼굴이 보이면 원의 위치 하나를 바꾸어 보세요.

예제 끝의 while처럼 실행할 문장이 하나이면 중괄호를 생략하기도 합니다. 직접 쓸 때는 중괄호로 묶어도 됩니다.

## Exercise — 신호등

검은색 또는 Gray 사각형 안에 Red, Yellow, Green 원 세 개가 세로로 들어 있는 신호등을 그리세요.

@exercise exercise1_starter.cpp

### Hint

먼저 FillRectangle로 몸체를 그리고 FillCircle을 세 번 사용하세요.

@solution exercise1_solution.cpp


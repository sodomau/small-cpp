---
title: 마우스를 따라가는 원
part: making_things
part-title: Part II — Making Things
goal: 마우스를 따라가는 원
related-example: reference/mouse
---

## 이번에 배울 것

**마우스 위치**도 창 안의 x, y 좌표로 읽을 수 있습니다.

## 실행해 보기

@code example1.cpp

MouseX와 MouseY가 돌려준 위치를 원의 중심으로 사용합니다. 매번 배경을 지우고 새 위치에 그리므로 원 하나가 마우스를 따라갑니다. 창 안에서 마우스를 움직여 보세요.

## Exercise — 클릭 위치 표시

왼쪽 버튼을 누르고 있는 동안 마우스 위치에 Yellow 원을 표시하고, 누르지 않을 때는 작은 Gray 원을 표시하세요.

@exercise exercise1_starter.cpp

### Hint

`MouseDown(MouseButton::Left)`로 두 경우를 나누세요.

@solution exercise1_solution.cpp


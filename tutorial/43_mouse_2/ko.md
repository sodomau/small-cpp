---
title: 마우스 버튼에 반응하기
part: making_things
part-title: 작은 걸음 II — 만들며 배우기
goal: 마우스 버튼에 반응하기
related-example: reference/mouse
---

## 이번에 배울 것

마우스의 **위치**와 **버튼 상태**는 별개입니다. 둘을 함께 읽으면 클릭한 곳에서 행동할 수 있습니다.

## 실행해 보기

@code example2.cpp

MouseDown(MouseButton::Left)은 왼쪽 버튼을 누르고 있는지 묻습니다. 누르는 동안 파란 원, 떼면 검은 테두리를 그립니다.

MousePressed는 누른 순간, MouseReleased는 뗀 순간입니다. 위치를 한 번 기억하려면 Pressed를 사용할 수 있습니다.

## Exercise — 두 버튼 두 색

왼쪽 버튼을 누르면 마우스 위치에 Red 원, 오른쪽 버튼을 누르면 Blue 원을 표시하세요.

@exercise exercise2_starter.cpp

### Hint

Left와 Right에 대해 각각 MouseDown을 검사하면 됩니다.

@solution exercise2_solution.cpp

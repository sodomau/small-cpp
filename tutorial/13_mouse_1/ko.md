---
title: 마우스로 조작하기
part: making_things
part-title: 작은 걸음 II — 만들며 배우기
goal: 마우스로 조작하기
related-example: reference/mouse
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 마우스를 따라가는 원

### 이번에 배울 것

**마우스 위치**도 창 안의 x, y 좌표로 읽을 수 있습니다.

### 실행해 보기

@code example1.cpp

mouse_x와 mouse_y가 돌려준 위치를 원의 중심으로 사용합니다. 매번 배경을 지우고 새 위치에 그리므로 원 하나가 마우스를 따라갑니다. 창 안에서 마우스를 움직여 보세요.

## 마우스 버튼에 반응하기

### 이번에 배울 것

마우스의 **위치**와 **버튼 상태**는 별개입니다. 둘을 함께 읽으면 클릭한 곳에서 행동할 수 있습니다.

### 실행해 보기

@code mouse_2_example2.cpp

mouse_down(MouseButton::Left)은 왼쪽 버튼을 누르고 있는지 묻습니다. 누르는 동안 파란 원, 떼면 검은 테두리를 그립니다.

mouse_pressed는 누른 순간, mouse_released는 뗀 순간입니다. 위치를 한 번 기억하려면 Pressed를 사용할 수 있습니다.

## Exercise — 클릭 위치 표시

왼쪽 버튼을 누르고 있는 동안 마우스 위치에 Yellow 원을 표시하고, 누르지 않을 때는 작은 Gray 원을 표시하세요.

@exercise exercise1_starter.cpp

### Hint

`mouse_down(MouseButton::Left)`로 두 경우를 나누세요.

@solution exercise1_solution.cpp

## 더 해 보기 (선택)

## Exercise — 두 버튼 두 색

왼쪽 버튼을 누르면 마우스 위치에 Red 원, 오른쪽 버튼을 누르면 Blue 원을 표시하세요.

@exercise mouse_2_exercise2_starter.cpp

### Hint

Left와 Right에 대해 각각 mouse_down을 검사하면 됩니다.

@solution mouse_2_exercise2_solution.cpp

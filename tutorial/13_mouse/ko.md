---
title: Mouse
part: making_things
part-title: Part II — Making Things
goal: 마우스 위치와 버튼 상태를 읽어 화면을 직접 조작합니다.
related-example: reference/mouse
---

## 마우스는 좌표를 알려 줍니다
Window 안에서 마우스가 있는 위치를 `MouseX()`와 `MouseY()`로 읽을 수 있습니다. 매 frame 그 위치에 원을 그리면 원이 마우스를 따라다닙니다.

## 먼저 실행해 보세요

@code example1.cpp

## 버튼도 키보드와 같은 세 가지 상태가 있습니다
`MouseDown`은 버튼을 누르고 있는 동안, `MousePressed`는 방금 누른 순간, `MouseReleased`는 방금 놓은 순간에 true입니다.

버튼은 `MouseButton::Left`, `MouseButton::Right`, `MouseButton::Middle`로 지정합니다.

## 조금 바꾸어 보기

@code example2.cpp

## 위치와 상태를 함께 사용하기
마우스 입력의 재미있는 점은 **어디에서** 일어났는지와 **무슨 버튼을 눌렀는지**를 함께 알 수 있다는 것입니다. 그래서 그림 그리기, 버튼, 간단한 drag 같은 interaction을 만들 수 있습니다.

지금 Window는 매 frame Clear하고 다시 그리는 방식이므로, 계속 남는 그림을 만들 때는 점들의 위치를 Array 등에 저장해 다시 그리는 방법도 생각할 수 있습니다.

## Exercise — 클릭 위치 표시

왼쪽 버튼을 누르고 있는 동안 마우스 위치에 Yellow 원을 표시하고, 누르지 않을 때는 작은 Gray 원을 표시하세요.

@exercise exercise1_starter.cpp

### Hint

`MouseDown(MouseButton::Left)`로 두 경우를 나누세요.

@solution exercise1_solution.cpp

## Exercise — 두 버튼 두 색

왼쪽 버튼을 누르면 마우스 위치에 Red 원, 오른쪽 버튼을 누르면 Blue 원을 표시하세요.

@exercise exercise2_starter.cpp

### Hint

Left와 Right에 대해 각각 MouseDown을 검사하면 됩니다.

@solution exercise2_solution.cpp

---
title: Drawing
part: making_things
part-title: Part II — Making Things
goal: Window에 색, 선, 사각형, 원과 글자를 그립니다.
related-example: reference/drawing
---

## 화면을 직접 채워 봅시다
Window는 단순히 빈 창만 여는 것이 아닙니다. 배경을 지우고, 선과 도형과 글자를 그릴 수 있습니다.

그림을 모두 준비한 뒤 `Show()`를 호출하면 그 결과가 화면에 나타납니다.

## 먼저 실행해 보세요

@code example1.cpp

## 좌표와 색
화면의 왼쪽 위가 `(0, 0)`입니다. x는 오른쪽으로, y는 아래쪽으로 커집니다. `RGB(red, green, blue)`로 직접 색을 만들 수도 있고 `Red`, `Blue`, `Yellow` 같은 기본 색을 사용할 수도 있습니다.

`DrawRectangle`은 테두리만, `FillRectangle`은 안쪽까지 채웁니다. Circle도 같은 방식입니다.

## 조금 바꾸어 보기

@code example2.cpp

## 그리는 순서도 중요합니다
나중에 그린 도형은 먼저 그린 도형 위에 나타납니다. 그래서 보통 배경을 먼저 Clear하고 큰 도형부터 그린 뒤 세부 요소와 글자를 그립니다.

다음 lesson부터는 매 frame마다 화면을 다시 그리면서 키보드와 마우스에 반응하게 됩니다.

## Exercise — 신호등

검은색 또는 Gray 사각형 안에 Red, Yellow, Green 원 세 개가 세로로 들어 있는 신호등을 그리세요.

@exercise exercise1_starter.cpp

### Hint

먼저 FillRectangle로 몸체를 그리고 FillCircle을 세 번 사용하세요.

@solution exercise1_solution.cpp

## Exercise — 나만의 얼굴

원과 선을 사용해 간단한 얼굴을 그리세요. 눈 두 개와 입이 보이면 됩니다. 색과 위치는 자유입니다.

@exercise exercise2_starter.cpp

### Hint

큰 FillCircle 하나를 얼굴로 만든 뒤 작은 원 두 개와 DrawLine을 추가해 보세요.

@solution exercise2_solution.cpp

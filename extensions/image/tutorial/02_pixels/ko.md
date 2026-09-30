---
title: Pixels
goal: Pixel과 SetPixel로 이미지의 개별 픽셀을 읽고 바꿉니다.
---

## 이미지는 픽셀의 격자입니다
`SetPixel(x, y, color)`로 한 픽셀의 색을 바꾸고 `Pixel(x, y)`로 읽을 수 있습니다. 좌표는 Window와 마찬가지로 왼쪽 위가 (0, 0)입니다.

## 먼저 실행해 보세요

@code example1.cpp

## 직접 픽셀을 만들면 알고리즘이 눈에 보입니다
두 겹의 loop로 모든 픽셀을 방문하면 gradient, pattern, 간단한 image processing을 직접 만들 수 있습니다. 범위를 벗어난 pixel 좌표는 오류로 처리됩니다.

## 한 단계 더

@code example2.cpp

## Pixel 작업과 drawing은 분리되어 있습니다
Image 안의 데이터를 바꾸는 것은 member function이고, 그 결과를 Window에 보여주는 것은 `DrawImage`입니다.

## Exercise — 대각선

100×100 Black 이미지에 (0,0)부터 (99,99)까지 Yellow 대각선을 그리세요.

@exercise exercise1_starter.cpp

### Hint

loop의 i를 x와 y에 모두 사용하세요.

@solution exercise1_solution.cpp

## Exercise — 픽셀 읽기

Red 이미지의 (10,10) 픽셀을 읽어 Red 성분을 출력하세요.

@exercise exercise2_starter.cpp

### Hint

`Color color = image.Pixel(10, 10);` 다음 `color.Red()`를 사용하세요.

@solution exercise2_solution.cpp

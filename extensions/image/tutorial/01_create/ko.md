---
title: 이미지 만들고 다루기
goal: 이미지 만들고 다루기
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## Creating Images

### 첫 Image extension
Image는 Core가 아니라 extension입니다. 그래서 첫 줄에서 `#include <small/image.h>`를 적습니다. Small IDE는 이 include를 보고 Image extension을 자동으로 연결합니다.

### 먼저 실행해 보세요

@code example1.cpp

### Image와 Window는 서로 다른 것
`Image`는 이미지 데이터를 소유하고 `width()`, `height()`, `pixel()` 같은 intrinsic operation을 제공합니다. `draw_image(window, image, ...)`는 Image와 Window의 관계이므로 free function입니다.

크기를 생략하면 원래 크기로 그리고, width와 height를 주면 그 크기로 부드럽게 확대/축소합니다.

### 한 단계 더

@code example2.cpp

### Extension도 그냥 C++입니다
Image를 사용한다고 새로운 언어를 배우는 것은 아닙니다. header 하나를 include하고 평범한 C++ object와 function을 사용하는 것입니다.

## Pixels

### 이미지는 픽셀의 격자입니다
`set_pixel(x, y, color)`로 한 픽셀의 색을 바꾸고 `pixel(x, y)`로 읽을 수 있습니다. 좌표는 Window와 마찬가지로 왼쪽 위가 (0, 0)입니다.

### 먼저 실행해 보세요

@code pixels_example1.cpp

### 직접 픽셀을 만들면 알고리즘이 눈에 보입니다
두 겹의 loop로 모든 픽셀을 방문하면 gradient, pattern, 간단한 image processing을 직접 만들 수 있습니다. 범위를 벗어난 pixel 좌표는 오류로 처리됩니다.

### 한 단계 더

@code pixels_example2.cpp

### Pixel 작업과 drawing은 분리되어 있습니다
Image 안의 데이터를 바꾸는 것은 member function이고, 그 결과를 Window에 보여주는 것은 `draw_image`입니다.

## Exercise — 두 크기로 그리기

120×80 Green 이미지를 만들고 원래 크기와 두 배 크기로 한 창에 그리세요.

@exercise exercise1_starter.cpp

### Hint

`draw_image`의 4-argument와 6-argument 형태를 각각 사용하세요.

@solution exercise1_solution.cpp

## Exercise — 크기 확인

64×48 이미지를 만들고 width와 height를 출력하세요.

@exercise exercise2_starter.cpp

### Hint

`print(image.width(), " x ", image.height());`를 사용하세요.

@solution exercise2_solution.cpp

## 더 해 보기 (선택)

## Exercise — 대각선

100×100 Black 이미지에 (0,0)부터 (99,99)까지 Yellow 대각선을 그리세요.

@exercise pixels_exercise1_starter.cpp

### Hint

loop의 i를 x와 y에 모두 사용하세요.

@solution pixels_exercise1_solution.cpp

## Exercise — 픽셀 읽기

Red 이미지의 (10,10) 픽셀을 읽어 Red 성분을 출력하세요.

@exercise pixels_exercise2_starter.cpp

### Hint

`Color color = image.pixel(10, 10);` 다음 `color.red()`를 사용하세요.

@solution pixels_exercise2_solution.cpp

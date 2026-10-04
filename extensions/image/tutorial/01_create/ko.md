---
title: Creating Images
goal: 메모리에서 Image를 만들고 Window에 그립니다.
---

## 첫 Image extension
Image는 Core가 아니라 extension입니다. 그래서 첫 줄에서 `#include <small/image.h>`를 적습니다. Small IDE는 이 include를 보고 Image extension을 자동으로 연결합니다.

## 먼저 실행해 보세요

@code example1.cpp

## Image와 Window는 서로 다른 것
`Image`는 이미지 데이터를 소유하고 `width()`, `height()`, `pixel()` 같은 intrinsic operation을 제공합니다. `draw_image(window, image, ...)`는 Image와 Window의 관계이므로 free function입니다.

크기를 생략하면 원래 크기로 그리고, width와 height를 주면 그 크기로 부드럽게 확대/축소합니다.

## 한 단계 더

@code example2.cpp

## Extension도 그냥 C++입니다
Image를 사용한다고 새로운 언어를 배우는 것은 아닙니다. header 하나를 include하고 평범한 C++ object와 function을 사용하는 것입니다.

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

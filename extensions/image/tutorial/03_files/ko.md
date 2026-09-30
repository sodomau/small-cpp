---
title: Loading and Saving
goal: 이미지 파일을 저장하고 다시 불러옵니다.
---

## 파일로 이어지는 Image
`Save()`는 Image를 파일로 저장하고, filename을 받는 constructor나 `Load()`는 파일을 읽습니다. PNG, JPEG 등 실제 지원 형식은 Qt image plugin이 제공하는 형식을 따릅니다.

## 먼저 실행해 보세요

@code example1.cpp

## 파일 이름이 format을 결정합니다
`SaveImage(image, "picture.png")`처럼 확장자를 쓰면 저장 형식을 정할 수 있습니다. 파일을 열 수 없거나 저장할 수 없으면 Small은 runtime error로 알려줍니다.

불러온 이미지의 alpha 정보는 DrawImage에서 그대로 합성됩니다.

## 한 단계 더

@code example2.cpp

## 이제 Image의 기본 흐름이 완성되었습니다
create/load → inspect/edit pixels → draw → save가 모두 가능합니다. 이 기능들은 Small IDE 밖에서도 평범한 C++ library API로 사용할 수 있도록 설계되어 있습니다.

## Exercise — 저장 후 읽기

50×50 Cyan 이미지를 `cyan.png`로 저장하고 새 Image로 다시 읽으세요.

@exercise exercise1_starter.cpp

### Hint

`Image loaded = LoadImage("cyan.png");`를 사용할 수 있습니다.

@solution exercise1_solution.cpp

## Exercise — 파일 수정

이미지를 만들고 저장한 뒤 다시 읽어서 (0,0)을 Magenta로 바꾸고 다른 이름으로 저장하세요.

@exercise exercise2_starter.cpp

### Hint

두 번째 저장 이름을 사용하면 원본 파일은 유지됩니다.

@solution exercise2_solution.cpp

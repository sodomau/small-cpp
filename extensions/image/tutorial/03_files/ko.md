---
title: Loading and Saving
goal: 이미지 파일을 저장하고 다시 불러옵니다.
---

## 파일로 이어지는 Image
`save_image(image, file_name)`은 Image를 파일로 저장하고, `load_image(file_name)`은 파일에서 Image를 읽습니다. PNG, JPEG 등 실제 지원 형식은 설치된 Qt image plugin에 따라 달라집니다.

## 먼저 실행해 보세요

@code example1.cpp

## 파일 이름이 format을 결정합니다
`save_image(image, "picture.png")`처럼 확장자를 쓰면 저장 형식을 정할 수 있습니다. 파일을 열 수 없거나 저장할 수 없으면 Small은 runtime error로 알려줍니다.

불러온 이미지의 alpha 정보는 draw_image에서 그대로 합성됩니다.

## 한 단계 더

@code example2.cpp

## 이제 Image의 기본 흐름이 완성되었습니다
create/load → inspect/edit pixels → draw → save가 모두 가능합니다. 이 기능들은 Small IDE 밖에서도 평범한 C++ library API로 사용할 수 있도록 설계되어 있습니다.

## Exercise — 저장 후 읽기

50×50 Cyan 이미지를 `cyan.png`로 저장하고 새 Image로 다시 읽으세요.

@exercise exercise1_starter.cpp

### Hint

`Image loaded = load_image("cyan.png");`를 사용할 수 있습니다.

@solution exercise1_solution.cpp

## Exercise — 파일 수정

이미지를 만들고 저장한 뒤 다시 읽어서 (0,0)을 Magenta로 바꾸고 다른 이름으로 저장하세요.

@exercise exercise2_starter.cpp

### Hint

두 번째 저장 이름을 사용하면 원본 파일은 유지됩니다.

@solution exercise2_solution.cpp

## 완성한 프로그램 공유하기

작은 걸음 VII — 프로그램 공유하기에서 Windows 배포본을 만드는 방법을 배울 수 있습니다. 프로그램이 불러오는 그림 파일은 Add Files로 함께 넣고, 폴더 전체를 ZIP으로 보내세요.

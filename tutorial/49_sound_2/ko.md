---
title: 소리가 끝날 때까지 기다리기
part: making_things
part-title: Part II — 만들며 배우기
goal: 소리가 끝날 때까지 기다리기
related-example: reference/sound
---

## 이번에 배울 것

**AndWait**이 붙은 함수는 소리가 끝날 때까지 기다렸다가 돌아옵니다.

## 실행해 보기

@code example2.cpp

BeepAndWait의 첫 값은 음의 높이를 정하는 주파수(Hz), 둘째 값은 초 단위 길이입니다. 440, 550, 660으로 높아지는 세 음 뒤에 효과음이 납니다.

게임 화면도 계속 움직여야 할 때는 기다리지 않는 PlaySound나 Beep이 편합니다.

## Exercise — 세 음 만들기

BeepAndWait를 사용해 서로 다른 주파수의 음 세 개를 차례대로 재생하세요. 주파수와 길이는 자유입니다.

@exercise exercise2_starter.cpp

### Hint

예를 들어 440, 550, 660 Hz를 각각 0.2초 정도 사용할 수 있습니다.

@solution exercise2_solution.cpp

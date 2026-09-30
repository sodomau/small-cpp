---
title: Sound
part: making_things
part-title: Part II — Making Things
goal: 미리 준비된 효과음과 간단한 beep를 재생하고 기다리는 재생과 비동기 재생을 구분합니다.
related-example: reference/sound
---

## 프로그램에 소리를 더하기
Small C++에는 바로 사용할 수 있는 몇 가지 효과음이 있습니다. `PlaySound`는 소리를 시작하고 프로그램은 바로 다음 줄로 진행합니다. 게임처럼 화면도 계속 움직여야 할 때 편합니다.

## 먼저 실행해 보세요

@code example1.cpp

## 기다릴 것인가, 계속할 것인가
`PlaySoundAndWait`는 소리가 끝날 때까지 기다린 뒤 다음 줄을 실행합니다. 여러 소리를 순서대로 들려줄 때 이해하기 쉽습니다.

`Beep(frequency, seconds)`는 주파수와 길이를 직접 지정한 간단한 음을 재생합니다. `BeepAndWait`도 같은 방식으로 기다립니다.

## 조금 바꾸어 보기

@code example2.cpp

## 게임에서는 보통 기다리지 않습니다
공이 벽에 부딪힐 때 효과음 때문에 animation이 멈추면 어색합니다. 이런 경우에는 `PlaySound`처럼 프로그램을 멈추지 않는 재생이 자연스럽습니다.

반대로 짧은 멜로디를 순서대로 들려주려면 AndWait 버전이 간단합니다.

## Exercise — 세 가지 효과음

Click, Coin, Win 효과음을 순서대로 들려주세요. 각 소리가 끝난 뒤 다음 소리가 시작되도록 하세요.

@exercise exercise1_starter.cpp

### Hint

`PlaySoundAndWait`를 세 번 사용하세요.

@solution exercise1_solution.cpp

## Exercise — 세 음 만들기

BeepAndWait를 사용해 서로 다른 주파수의 음 세 개를 차례대로 재생하세요. 주파수와 길이는 자유입니다.

@exercise exercise2_starter.cpp

### Hint

예를 들어 440, 550, 660 Hz를 각각 0.2초 정도 사용할 수 있습니다.

@solution exercise2_solution.cpp

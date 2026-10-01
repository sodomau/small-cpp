---
title: 효과음 재생하기
part: making_things
part-title: Part II — 만들며 배우기
goal: 효과음 재생하기
related-example: reference/sound
---

## 이번에 배울 것

**소리 재생**은 시간이 걸리는 작업입니다. 함수를 호출한 뒤 소리가 끝나기 전에 프로그램이 다음 일을 할 수도 있습니다.

## 실행해 보기

@code example1.cpp

PlaySound는 재생을 시작하고 바로 돌아옵니다. Sound::Pop과 Sound::Coin은 준비된 효과음 이름입니다.

예제에서는 프로그램이 바로 끝나지 않도록 Sleep으로 기다립니다. 두 효과음이 순서대로 시작되는지 들어 보세요.

## Exercise — 세 가지 효과음

Click, Coin, Win 효과음을 순서대로 들려주세요. 각 소리가 끝난 뒤 다음 소리가 시작되도록 하세요.

@exercise exercise1_starter.cpp

### Hint

`PlaySoundAndWait`를 세 번 사용하세요.

@solution exercise1_solution.cpp


---
title: 소리 재생하기
part: making_things
part-title: 작은 걸음 II — 만들며 배우기
goal: 소리 재생하기
related-example: reference/sound
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 효과음 재생하기

### 이번에 배울 것

**소리 재생**은 시간이 걸리는 작업입니다. 함수를 호출한 뒤 소리가 끝나기 전에 프로그램이 다음 일을 할 수도 있습니다.

### 실행해 보기

@code example1.cpp

play_sound는 재생을 시작하고 바로 돌아옵니다. Sound::Pop과 Sound::Coin은 준비된 효과음 이름입니다.

예제에서는 프로그램이 바로 끝나지 않도록 sleep으로 기다립니다. 두 효과음이 순서대로 시작되는지 들어 보세요.

## 소리가 끝날 때까지 기다리기

### 이번에 배울 것

**AndWait**이 붙은 함수는 소리가 끝날 때까지 기다렸다가 돌아옵니다.

### 실행해 보기

@code sound_2_example2.cpp

beep_and_wait의 첫 값은 음의 높이를 정하는 주파수(Hz), 둘째 값은 초 단위 길이입니다. 440, 550, 660으로 높아지는 세 음 뒤에 효과음이 납니다.

게임 화면도 계속 움직여야 할 때는 기다리지 않는 play_sound나 beep이 편합니다.

## Exercise — 세 가지 효과음

Click, Coin, Win 효과음을 순서대로 들려주세요. 각 소리가 끝난 뒤 다음 소리가 시작되도록 하세요.

@exercise exercise1_starter.cpp

### Hint

`play_sound_and_wait`를 세 번 사용하세요.

@solution exercise1_solution.cpp

## 더 해 보기 (선택)

## Exercise — 세 음 만들기

beep_and_wait를 사용해 서로 다른 주파수의 음 세 개를 차례대로 재생하세요. 주파수와 길이는 자유입니다.

@exercise sound_2_exercise2_starter.cpp

### Hint

예를 들어 440, 550, 660 Hz를 각각 0.2초 정도 사용할 수 있습니다.

@solution sound_2_exercise2_solution.cpp

## 직접 준비한 WAV 소리

`play_sound("sound.wav");`처럼 파일 경로도 전달할 수 있습니다. 16비트 PCM WAV 파일(모노 또는 스테레오)을 프로그램 폴더에 놓으세요. 배포할 때는 Publish → Add Files로 함께 넣습니다. 처음에는 뒤에서 로딩하고, 다음부터는 캐시를 재사용합니다. 타이밍이 중요한 효과음은 게임 시작 전에 `preload_sound("sound.wav");`로 미리 준비할 수 있습니다. 이 함수는 로딩이 끝날 때까지 기다리지만 소리는 재생하지 않습니다. `play_sound_and_wait("sound.wav");`는 재생이 끝날 때까지 기다립니다.

```cpp
void small_main()
{
    preload_sound("sound.wav"); // Optional
    play_sound("sound.wav");
    print("The program keeps running.");
    sleep(1);
    play_sound_and_wait("sound.wav");
}
```
직접 실행할 수 있는 프로젝트와 자체 제작 sound.wav는 `examples/projects/WavSound`에 들어 있습니다. 해당 폴더를 프로젝트로 여세요.

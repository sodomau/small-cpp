---
title: 키보드로 조작하기
part: making_things
part-title: 작은 걸음 II — 만들며 배우기
goal: 키보드로 조작하기
related-example: reference/keyboard
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 키를 누르는 동안 움직이기

### 이번에 배울 것

**키 입력 상태**는 지금 어떤 키가 눌려 있는지 알려 줍니다. key_down은 키를 누르고 있는 동안 참입니다.

### 실행해 보기

@code example1.cpp

방향키로 x와 y를 바꾸고 그 위치에 원을 다시 그립니다. 한 번의 반복에서 만든 화면을 **프레임**이라고 합니다.

`Key::Left`는 왼쪽 방향키를 가리키는 이름입니다. 왼쪽·오른쪽 키를 길게 눌러 원이 계속 움직이는지 보세요.

## 한 번 누를 때 한 번 바꾸기

### 이번에 배울 것

**key_pressed**는 새로 누른 순간을 알려 줍니다. 길게 눌러도 매 프레임 참이 되는 key_down과 구분합니다.

### 실행해 보기

@code keyboard_2_example2.cpp

Space를 새로 누를 때 `is_red = !is_red;`로 참과 거짓을 뒤집습니다. 그 값에 따라 빨강과 파랑을 고릅니다. Space를 길게 눌렀다가 떼고 다시 눌러 보세요.

key_released는 키를 뗀 순간을 알려 줍니다. 이동에는 Down, 한 번 바꾸는 동작에는 Pressed가 편합니다.

## Exercise — WASD로 움직이기

방향키 대신 W, A, S, D를 사용해 원을 위, 왼쪽, 아래, 오른쪽으로 움직이세요.

@exercise exercise1_starter.cpp

### Hint

문자 키는 `window.key_down('W')`처럼 확인할 수 있습니다.

@solution exercise1_solution.cpp

## 더 해 보기 (선택)

## Exercise — Space로 크기 바꾸기

Space를 누를 때마다 원의 radius가 20과 60 사이에서 바뀌게 하세요. 누르고 있는 동안 계속 바뀌면 안 됩니다.

@exercise keyboard_2_exercise2_starter.cpp

### Hint

`key_pressed(Key::Space)`와 bool 변수를 사용해 두 상태를 번갈아 보세요.

@solution keyboard_2_exercise2_solution.cpp

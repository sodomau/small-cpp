---
title: 한 번 누를 때 한 번 바꾸기
part: making_things
part-title: 작은 걸음 II — 만들며 배우기
goal: 한 번 누를 때 한 번 바꾸기
related-example: reference/keyboard
---

## 이번에 배울 것

**key_pressed**는 새로 누른 순간을 알려 줍니다. 길게 눌러도 매 프레임 참이 되는 key_down과 구분합니다.

## 실행해 보기

@code example2.cpp

Space를 새로 누를 때 `is_red = !is_red;`로 참과 거짓을 뒤집습니다. 그 값에 따라 빨강과 파랑을 고릅니다. Space를 길게 눌렀다가 떼고 다시 눌러 보세요.

key_released는 키를 뗀 순간을 알려 줍니다. 이동에는 Down, 한 번 바꾸는 동작에는 Pressed가 편합니다.

## Exercise — Space로 크기 바꾸기

Space를 누를 때마다 원의 radius가 20과 60 사이에서 바뀌게 하세요. 누르고 있는 동안 계속 바뀌면 안 됩니다.

@exercise exercise2_starter.cpp

### Hint

`key_pressed(Key::Space)`와 bool 변수를 사용해 두 상태를 번갈아 보세요.

@solution exercise2_solution.cpp

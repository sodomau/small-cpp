---
title: Keyboard
part: making_things
part-title: Part II — Making Things
goal: 키가 눌려 있는지 또는 방금 눌렸는지 확인해 프로그램을 조작합니다.
related-example: reference/keyboard
---

## 프로그램이 내 입력에 반응하게
게임에서는 사용자가 키를 누르는 동안 계속 움직이기도 하고, 한 번 누른 순간에만 어떤 일이 일어나기도 합니다.

`KeyDown`은 키가 **지금 눌려 있는 동안** true입니다. 먼저 방향키로 원을 움직여 봅시다.

## 먼저 실행해 보세요

@code example1.cpp

## Down과 Pressed의 차이
`KeyDown`은 키를 누르고 있는 여러 frame 동안 true가 될 수 있습니다. `KeyPressed`는 **눌리지 않은 상태에서 눌린 상태로 바뀐 순간**에 한 번만 true가 됩니다. 색을 한 번씩 바꾸거나 총알을 한 발 발사할 때 유용합니다.

특수 키는 `Key::Space`, `Key::Escape`처럼 쓰고 글자 키는 `'A'`처럼 쓸 수도 있습니다.

## 조금 바꾸어 보기

@code example2.cpp

## 같은 입력이라도 원하는 행동이 다릅니다
계속 움직여야 하면 `KeyDown`, 한 번만 일어나야 하면 `KeyPressed`가 자연스럽습니다. 키를 놓은 순간이 필요할 때는 `KeyReleased`도 있습니다.

다음에는 같은 방식으로 마우스의 위치와 버튼 상태를 읽어 봅니다.

## Exercise — WASD로 움직이기

방향키 대신 W, A, S, D를 사용해 원을 위, 왼쪽, 아래, 오른쪽으로 움직이세요.

@exercise exercise1_starter.cpp

### Hint

문자 키는 `window.KeyDown('W')`처럼 확인할 수 있습니다.

@solution exercise1_solution.cpp

## Exercise — Space로 크기 바꾸기

Space를 누를 때마다 원의 radius가 20과 60 사이에서 바뀌게 하세요. 누르고 있는 동안 계속 바뀌면 안 됩니다.

@exercise exercise2_starter.cpp

### Hint

`KeyPressed(Key::Space)`와 bool 변수를 사용해 두 상태를 번갈아 보세요.

@solution exercise2_solution.cpp

---
title: 키를 누르는 동안 움직이기
part: making_things
part-title: 작은 걸음 II — 만들며 배우기
goal: 키를 누르는 동안 움직이기
related-example: reference/keyboard
---

## 이번에 배울 것

**키 입력 상태**는 지금 어떤 키가 눌려 있는지 알려 줍니다. key_down은 키를 누르고 있는 동안 참입니다.

## 실행해 보기

@code example1.cpp

방향키로 x와 y를 바꾸고 그 위치에 원을 다시 그립니다. 한 번의 반복에서 만든 화면을 **프레임**이라고 합니다.

`Key::Left`는 왼쪽 방향키를 가리키는 이름입니다. 왼쪽·오른쪽 키를 길게 눌러 원이 계속 움직이는지 보세요.

## Exercise — WASD로 움직이기

방향키 대신 W, A, S, D를 사용해 원을 위, 왼쪽, 아래, 오른쪽으로 움직이세요.

@exercise exercise1_starter.cpp

### Hint

문자 키는 `window.key_down('W')`처럼 확인할 수 있습니다.

@solution exercise1_solution.cpp


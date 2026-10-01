---
title: 위치를 바꾸며 다시 그리기
part: making_things
part-title: Part II — 만들며 배우기
goal: 위치를 바꾸며 다시 그리기
related-example: programs/bouncing_ball
---

## 이번에 배울 것

**애니메이션**은 상태를 조금씩 바꾸며 그림을 연속해서 보여 주는 것입니다. 이번에는 원의 x 위치를 바꿉니다.

## 실행해 보기

@code example1.cpp

반복할 때마다 x를 2 늘리고, 배경을 지우고, 원을 그려 보여 줍니다. 오른쪽을 넘으면 x를 0으로 되돌립니다.

Sleep(0.01)은 약 0.01초 기다립니다. 원이 오른쪽으로 움직이다 왼쪽에서 다시 나타나는지 보세요.

## Exercise — 위아래로 움직이기

원을 화면 중앙 x=320에 두고 y 방향으로 움직이게 하세요. 위와 아래 끝에 닿으면 방향을 바꾸세요.

@exercise exercise1_starter.cpp

### Hint

y와 speed를 만들고, `y > 460 || y < 20`이면 speed의 부호를 바꾸세요.

@solution exercise1_solution.cpp


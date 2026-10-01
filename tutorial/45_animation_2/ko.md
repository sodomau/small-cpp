---
title: 방향 바꾸어 튕기기
part: making_things
part-title: 작은 걸음 II — 만들며 배우기
goal: 방향 바꾸어 튕기기
related-example: programs/bouncing_ball
---

## 이번에 배울 것

움직이는 방향을 속도 값의 부호로 나타낼 수 있습니다. 양수이면 오른쪽, 음수이면 왼쪽으로 갑니다.

## 실행해 보기

@code example2.cpp

경계에 닿으면 `speed = -speed;`로 부호를 뒤집습니다. 반지름 20을 고려해 중심이 20과 620 사이에 머무르게 합니다.

지금의 속도는 반복 한 번당 이동량입니다. 컴퓨터마다 반복 속도가 달라질 수 있어 다음에는 실제 시간을 사용합니다.

## Exercise — 두 공 움직이기

서로 다른 x 위치와 속도를 가진 공 두 개를 같은 화면에서 움직이세요. 둘 다 오른쪽 끝을 지나면 왼쪽에서 다시 시작하게 하세요.

@exercise exercise2_starter.cpp

### Hint

x1, x2와 speed1, speed2를 각각 만들면 됩니다.

@solution exercise2_solution.cpp

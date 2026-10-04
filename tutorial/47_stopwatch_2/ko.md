---
title: 실제 시간에 맞춰 움직이기
part: making_things
part-title: 작은 걸음 II — 만들며 배우기
goal: 실제 시간에 맞춰 움직이기
related-example: reference/stopwatch
---

## 이번에 배울 것

이동 거리 = 속도 × 시간입니다. 초당 속도를 정하고, 지난 시간만큼 이동하면 반복 속도가 달라도 움직임을 맞출 수 있습니다.

## 실행해 보기

@code example2.cpp

dt는 지난 반복부터 흐른 시간을 담는 변수입니다. elapsed로 읽은 뒤 reset하고 `speed * dt`를 위치에 더합니다.

속도가 초당 200픽셀이면 0.01초에는 2픽셀, 0.02초에는 4픽셀 움직입니다. dt는 새 문법이 아닙니다. speed를 100으로 바꾸어 비교하세요.

## Exercise — 시간 기준으로 움직이기

수업 44의 위아래 움직이는 공을 고쳐서 speed를 초당 150 pixel로 만들고 dt를 사용하세요.

@exercise exercise2_starter.cpp

### Hint

loop마다 `double dt = watch.elapsed(); watch.reset();`을 하고 `y = y + speed * dt;`로 이동하세요.

@solution exercise2_solution.cpp

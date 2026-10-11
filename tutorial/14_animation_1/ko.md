---
title: 움직이는 그림 만들기
part: making_things
part-title: 작은 걸음 II — 만들며 배우기
goal: 움직이는 그림 만들기
related-example: programs/bouncing_ball
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 위치를 바꾸며 다시 그리기

### 이번에 배울 것

**애니메이션**은 상태를 조금씩 바꾸며 그림을 연속해서 보여 주는 것입니다. 이번에는 원의 x 위치를 바꿉니다.

### 실행해 보기

@code example1.cpp

반복할 때마다 x를 2 늘리고, 배경을 지우고, 원을 그려 보여 줍니다. 오른쪽을 넘으면 x를 0으로 되돌립니다.

sleep(0.01)은 약 0.01초 기다립니다. 원이 오른쪽으로 움직이다 왼쪽에서 다시 나타나는지 보세요.

## 방향 바꾸어 튕기기

### 이번에 배울 것

움직이는 방향을 속도 값의 부호로 나타낼 수 있습니다. 양수이면 오른쪽, 음수이면 왼쪽으로 갑니다.

### 실행해 보기

@code animation_2_example2.cpp

경계에 닿으면 `speed = -speed;`로 부호를 뒤집습니다. 반지름 20을 고려해 중심이 20과 620 사이에 머무르게 합니다.

지금의 속도는 반복 한 번당 이동량입니다. 컴퓨터마다 반복 속도가 달라질 수 있어 다음에는 실제 시간을 사용합니다.

## 지난 시간 재기

### 이번에 배울 것

**StopWatch**는 경과 시간을 재는 도구입니다. 객체를 만들 때부터 시간을 재고 elapsed는 지난 초 수를 알려 줍니다.

### 실행해 보기

@code stopwatch_1_example1.cpp

sleep(1.0) 뒤에는 약 1초, `reset` 후 sleep(0.5) 뒤에는 약 0.5초가 나옵니다. 읽기만 한다고 시계가 0으로 돌아가지는 않습니다. reset이 다시 재는 동작입니다.

실행 환경 때문에 정확히 1.000이나 0.500이 아니어도 정상입니다.

## 실제 시간에 맞춰 움직이기

### 이번에 배울 것

이동 거리 = 속도 × 시간입니다. 초당 속도를 정하고, 지난 시간만큼 이동하면 반복 속도가 달라도 움직임을 맞출 수 있습니다.

### 실행해 보기

@code stopwatch_2_example2.cpp

dt는 지난 반복부터 흐른 시간을 담는 변수입니다. elapsed로 읽은 뒤 reset하고 `speed * dt`를 위치에 더합니다.

속도가 초당 200픽셀이면 0.01초에는 2픽셀, 0.02초에는 4픽셀 움직입니다. dt는 새 문법이 아닙니다. speed를 100으로 바꾸어 비교하세요.

## Exercise — 위아래로 움직이기

원을 화면 중앙 x=320에 두고 y 방향으로 움직이게 하세요. 위와 아래 끝에 닿으면 방향을 바꾸세요.

@exercise exercise1_starter.cpp

### Hint

y와 speed를 만들고, `y > 460 || y < 20`이면 speed의 부호를 바꾸세요.

@solution exercise1_solution.cpp

## 더 해 보기 (선택)

## Exercise — 두 공 움직이기

서로 다른 x 위치와 속도를 가진 공 두 개를 같은 화면에서 움직이세요. 둘 다 오른쪽 끝을 지나면 왼쪽에서 다시 시작하게 하세요.

@exercise animation_2_exercise2_starter.cpp

### Hint

x1, x2와 speed1, speed2를 각각 만들면 됩니다.

@solution animation_2_exercise2_solution.cpp

## Exercise — 2초 재기

StopWatch를 만들고 sleep(2.0) 뒤 `elapsed` 값을 출력하세요. 정확히 2.000...이 아니어도 정상입니다.

@exercise stopwatch_1_exercise1_starter.cpp

### Hint

StopWatch는 생성되는 순간 시작하므로 별도의 start가 필요 없습니다.

@solution stopwatch_1_exercise1_solution.cpp

## Exercise — 시간 기준으로 움직이기

수업 44의 위아래 움직이는 공을 고쳐서 speed를 초당 150 pixel로 만들고 dt를 사용하세요.

@exercise stopwatch_2_exercise2_starter.cpp

### Hint

loop마다 `double dt = watch.elapsed(); watch.reset();`을 하고 `y = y + speed * dt;`로 이동하세요.

@solution stopwatch_2_exercise2_solution.cpp

---
title: Animation
part: making_things
part-title: Part II — Making Things
goal: frame마다 값을 조금씩 바꾸고 다시 그려 움직임을 만듭니다.
related-example: programs/bouncing_ball
---

## 움직임은 여러 장의 그림입니다
컴퓨터 animation은 한 장의 그림이 실제로 움직이는 것이 아닙니다. 아주 짧은 시간마다 위치를 조금 바꾸어 다시 그립니다. 각각의 화면을 **frame**이라고 부릅니다.

먼저 x를 frame마다 2씩 증가시켜 원을 움직여 봅시다.

## 먼저 실행해 보세요

@code example1.cpp

## update한 뒤 draw하기
animation loop에서는 보통 먼저 위치나 상태를 **update**하고, 그 결과를 **draw**합니다. `Clear`로 이전 frame을 지우고 새 위치에 다시 그린 뒤 `Show`합니다.

하지만 지금 코드는 한 가지 문제가 있습니다. `x = x + 2`는 **frame당** 이동량입니다. 컴퓨터가 더 많은 frame을 그리면 공도 더 빨라집니다.

## 조금 바꾸어 보기

@code example2.cpp

## 다음 lesson에서 고칠 문제
`Sleep(0.01)`로 속도를 대충 맞출 수는 있지만 정확한 해결은 아닙니다. 실제로 frame 하나에 얼마나 시간이 걸렸는지를 측정하면 **초당 몇 pixel**처럼 속도를 표현할 수 있습니다.

그래서 다음에는 StopWatch로 시간을 재고, animation을 컴퓨터 속도와 분리합니다.

## Exercise — 위아래로 움직이기

원을 화면 중앙 x=320에 두고 y 방향으로 움직이게 하세요. 위와 아래 끝에 닿으면 방향을 바꾸세요.

@exercise exercise1_starter.cpp

### Hint

y와 speed를 만들고, `y > 460 || y < 20`이면 speed의 부호를 바꾸세요.

@solution exercise1_solution.cpp

## Exercise — 두 공 움직이기

서로 다른 x 위치와 속도를 가진 공 두 개를 같은 화면에서 움직이세요. 둘 다 오른쪽 끝을 지나면 왼쪽에서 다시 시작하게 하세요.

@exercise exercise2_starter.cpp

### Hint

x1, x2와 speed1, speed2를 각각 만들면 됩니다.

@solution exercise2_solution.cpp

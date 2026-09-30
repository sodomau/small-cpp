---
title: Measuring Time — StopWatch
part: making_things
part-title: Part II — Making Things
goal: StopWatch로 실제 경과 시간을 측정하고 animation을 시간 기준으로 움직입니다.
related-example: reference/stopwatch
---

## 현실의 스톱워치처럼
`StopWatch`는 만들어지는 순간부터 시간이 흐릅니다. `Elapsed()`는 몇 초가 지났는지 알려주고 `Reset()`은 다시 0부터 재기 시작합니다.

먼저 단순히 시간을 재어 봅시다.

## 먼저 실행해 보세요

@code example1.cpp

## frame time을 이용하기
animation loop의 시작에서 지난 frame 이후 걸린 시간을 `dt`로 구할 수 있습니다. 속도가 `200`이면 **초당 200 pixel**이라는 뜻으로 사용할 수 있습니다.

`x = x + speed * dt`라고 하면 frame이 빠른 컴퓨터에서는 dt가 작아지고, 느린 컴퓨터에서는 dt가 커져서 같은 실제 시간 동안 비슷한 거리를 움직입니다.

## 조금 바꾸어 보기

@code example2.cpp

## dt는 elapsed time의 작은 조각입니다
`dt`는 delta time의 흔한 이름입니다. 특별한 Small 문법이 아니라 우리가 정한 변수 이름일 뿐입니다.

StopWatch는 animation뿐 아니라 reaction time, 코드가 걸린 시간, 게임 플레이 시간처럼 현실의 시간을 측정할 때도 그대로 사용할 수 있습니다.

## Exercise — 2초 재기

StopWatch를 만들고 Sleep(2.0) 뒤 Elapsed 값을 출력하세요. 정확히 2.000...이 아니어도 정상입니다.

@exercise exercise1_starter.cpp

### Hint

StopWatch는 생성되는 순간 시작하므로 별도의 Start가 필요 없습니다.

@solution exercise1_solution.cpp

## Exercise — 시간 기준으로 움직이기

Lesson 14의 위아래 움직이는 공을 고쳐서 speed를 초당 150 pixel로 만들고 dt를 사용하세요.

@exercise exercise2_starter.cpp

### Hint

loop마다 `double dt = watch.Elapsed(); watch.Reset();`을 하고 `y = y + speed * dt;`로 이동하세요.

@solution exercise2_solution.cpp

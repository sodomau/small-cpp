---
title: 시간이 되면 함수 실행하기
part: making_things
part-title: 작은 걸음 II — 만들며 배우기
goal: 시간이 되면 함수 실행하기
related-example: reference/timer
---

## 이번에 배울 것

**이벤트**는 프로그램이 반응할 사건이고, **콜백**은 그 사건 때 실행하도록 맡겨 둔 함수입니다. Timer로 약 1초마다 함수를 실행합니다.

## 실행해 보기

@code example1.cpp

start(1.0, on_timer)에서 on_timer 뒤에 ()가 없는 이유는 지금 실행하는 대신 실행할 함수를 지정하기 때문입니다.

모든 함수 밖의 ticks는 여러 함수가 사용하는 **전역 변수**입니다. 콜백마다 1을 더합니다. sleep 중에도 타이머가 처리되고 stop하면 멈춥니다. 시간 예약이므로 정확한 호출 횟수를 보장하지는 않습니다.

## Exercise — 0.5초마다 세기

0.5초마다 호출되는 callback을 만들고 count를 1씩 증가시키며 출력하세요. 약 2.2초 뒤 Timer를 멈추세요.

@exercise exercise1_starter.cpp

### Hint

`timer.start(0.5, on_timer)`를 사용하고 callback에서 count를 증가시키세요.

@solution exercise1_solution.cpp


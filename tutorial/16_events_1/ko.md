---
title: 타이머 사용하기
part: making_things
part-title: 작은 걸음 II — 만들며 배우기
goal: 타이머 사용하기
related-example: reference/timer
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 시간이 되면 함수 실행하기

### 이번에 배울 것

**이벤트**는 프로그램이 반응할 사건이고, **콜백**은 그 사건 때 실행하도록 맡겨 둔 함수입니다. Timer로 약 1초마다 함수를 실행합니다.

### 실행해 보기

@code example1.cpp

start(1.0, on_timer)에서 on_timer 뒤에 ()가 없는 이유는 지금 실행하는 대신 실행할 함수를 지정하기 때문입니다.

모든 함수 밖의 ticks는 여러 함수가 사용하는 **전역 변수**입니다. 콜백마다 1을 더합니다. sleep 중에도 타이머가 처리되고 stop하면 멈춥니다. 시간 예약이므로 정확한 호출 횟수를 보장하지는 않습니다.

## 타이머의 값을 화면에 표시하기

### 이번에 배울 것

콜백에서는 값을 바꾸고, 창의 반복문에서는 그 값을 읽어 그림을 그릴 수 있습니다.

### 실행해 보기

@code events_2_example2.cpp

on_second가 전역 seconds를 늘리고 draw_text가 현재 값을 표시합니다. `format`은 글자와 값을 이어 붙인 String을 돌려줍니다. print와 달리 직접 출력하지 않습니다.

Timer는 별도 계산 스레드가 아닙니다. show나 sleep이 이벤트를 처리할 때 콜백을 실행하므로 긴 계산은 호출을 늦출 수 있습니다. 정확한 시간 측정은 StopWatch로 하세요.

## Exercise — 0.5초마다 세기

0.5초마다 호출되는 callback을 만들고 count를 1씩 증가시키며 출력하세요. 약 2.2초 뒤 Timer를 멈추세요.

@exercise exercise1_starter.cpp

### Hint

`timer.start(0.5, on_timer)`를 사용하고 callback에서 count를 증가시키세요.

@solution exercise1_solution.cpp

## 더 해 보기 (선택)

## Exercise — 창의 제목 바꾸기

Timer callback이 1초마다 level을 1씩 증가시키게 하세요. Window loop에서는 현재 level을 `set_title("Level ", level)`로 제목에 표시하세요.

@exercise events_2_exercise2_starter.cpp

### Hint

callback에서는 전역 int level만 바꾸고, Window title은 main loop에서 갱신하면 간단합니다.

@solution events_2_exercise2_solution.cpp

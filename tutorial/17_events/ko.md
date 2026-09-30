---
title: Events — Timer and Callbacks
part: making_things
part-title: Part II — Making Things
goal: Timer와 callback으로 일정 시간이 지날 때 함수를 자동으로 호출하게 합니다.
related-example: reference/timer
---

## 시간이 되면 어떤 일을 시키기
지금까지 프로그램의 흐름은 대부분 `SmallMain`의 위에서 아래로 진행되었습니다. 하지만 어떤 일은 **1초마다**, 또는 **일정한 간격마다** 일어나게 하고 싶습니다.

`Timer`는 정해진 시간이 지날 때마다 우리가 지정한 함수를 호출할 수 있습니다. 이런 함수를 **callback**이라고 부릅니다.

## 먼저 실행해 보세요

@code example1.cpp

## 함수 자체를 전달하기
`timer.Start(1.0, OnTimer);`에서 `OnTimer` 뒤에는 괄호가 없습니다. 지금 OnTimer를 실행하는 것이 아니라, **나중에 Timer가 호출할 함수**로 알려주는 것입니다.

callback은 parameter가 없고 return type이 void인 간단한 함수로 시작합니다. Timer가 실행되는 동안 SmallMain도 자기 일을 계속할 수 있습니다.

## 조금 바꾸어 보기

@code example2.cpp

## Event-based programming의 첫 맛
Timer는 프로그램이 계속 실행되는 동안 특정 사건이 생겼을 때 callback을 호출합니다. GUI, 게임, 네트워크 프로그램에서도 이런 **event** 개념을 많이 만납니다.

지금은 callback이 전역 함수이고 공유하는 변수도 간단히 바깥에 두었습니다. 뒤에서 class를 배우면 관련된 상태와 행동을 한 객체에 묶는 방법도 이해할 수 있습니다.

## Exercise — 0.5초마다 세기

0.5초마다 호출되는 callback을 만들고 count를 1씩 증가시키며 출력하세요. 약 2.2초 뒤 Timer를 멈추세요.

@exercise exercise1_starter.cpp

### Hint

`timer.Start(0.5, OnTimer)`를 사용하고 callback에서 count를 증가시키세요.

@solution exercise1_solution.cpp

## Exercise — 창의 제목 바꾸기

Timer callback이 1초마다 level을 1씩 증가시키게 하세요. Window loop에서는 현재 level을 `SetTitle("Level ", level)`로 제목에 표시하세요.

@exercise exercise2_starter.cpp

### Hint

callback에서는 전역 int level만 바꾸고, Window title은 main loop에서 갱신하면 간단합니다.

@solution exercise2_solution.cpp

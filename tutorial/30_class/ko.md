---
title: class — Data and Behavior
part: types
part-title: Part V — Making Your Own Types
goal: data와 그 data를 다루는 함수를 하나의 class에 묶고 public/private의 역할을 이해합니다.
related-example: programs/bouncing_ball
---

## data가 할 수 있는 일까지 묶기
Player의 위치를 바꾸는 코드를 프로그램 곳곳에서 직접 작성하는 대신 Player에게 `Move`라는 행동을 줄 수 있습니다.

`class`는 data와 function을 같은 type 안에 넣을 수 있습니다. class 안의 함수를 **member function**이라고 부릅니다.

## 먼저 실행해 보세요

@code example1.cpp

## public은 사용하는 쪽, private은 내부
`public` 아래의 member는 object를 사용하는 코드에서 호출할 수 있습니다. `private` 아래의 data는 class 안의 함수만 직접 사용할 수 있습니다.

Counter를 사용하는 사람은 value가 내부에서 어떻게 저장되는지 몰라도 `AddOne()`과 `Value()`만 알면 됩니다. 이것이 class가 구현의 세부사항을 감추는 기본적인 방법입니다.

우리가 이미 사용한 `Window`, `String`, `StopWatch`, `File`도 이런 class입니다.

## 조금 바꾸어 보기

@code example2.cpp

## 여기서 처음 보이는 `Window&`
Ball의 `Draw`는 이미 열려 있는 **같은 Window**에 그려야 합니다. Window는 복사할 수 없는 객체이므로 여기서는 `Window&`를 사용합니다.

지금은 `&`를 “기존 Window를 그대로 사용한다”는 표지 정도로만 보고 넘어갑니다. 바로 다음 Lesson 31에서 **왜 필요한지, 메모리에서 무엇이 다른지**를 처음부터 설명합니다. 이 한 곳은 다음 개념으로 넘어가기 위한 의도적인 예고입니다.

## Exercise — Counter에 Reset 추가

Counter class에 값을 0으로 만드는 public `Reset()`을 추가하고 동작을 확인하세요.

@exercise exercise1_starter.cpp

### Hint

Reset 안에서 private value에 0을 대입하세요.

@solution exercise1_solution.cpp

## Exercise — 움직이는 Ball

Ball class에 x와 speed를 private data로 두고 Move와 X member function을 만드세요. Move를 세 번 호출한 뒤 X를 출력하세요.

@exercise exercise2_starter.cpp

### Hint

Move에서는 x에 speed를 더하고 X에서는 `return x;`를 사용하세요.

@solution exercise2_solution.cpp

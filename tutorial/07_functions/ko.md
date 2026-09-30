---
title: Functions
part: basics
part-title: Part I — Programming Basics
goal: 함수로 코드를 이름 붙여 묶고, 값을 전달하거나 결과를 돌려받습니다.
related-example: reference/console
---

## 자주 하는 일을 이름 붙이기
프로그램이 길어지면 여러 줄의 코드가 하나의 일을 한다는 사실이 잘 보이지 않을 수 있습니다. **함수**를 만들면 그 일에 이름을 붙이고 필요할 때 호출할 수 있습니다.

아래의 `PrintLine`은 별표 열 개를 출력하는 함수입니다. `SmallMain`도 함수이고, 우리가 직접 함수를 더 만들 수 있습니다.

## `void`는 돌려주는 값이 없다는 뜻입니다
함수 이름 앞에는 그 함수가 어떤 종류의 값을 돌려주는지가 적힙니다. 이것을 **return type**이라고 합니다.

`void PrintLine()`에서 `void`는 **이 함수가 결과값을 돌려주지 않는다**는 뜻입니다. `PrintLine`은 별표를 출력하는 일을 하고 그대로 끝납니다.

함수의 기본 모양에서 `void`는 돌려주는 값이 없음을, `PrintLine`은 함수의 이름을, `()`는 지금 받을 parameter가 없음을, `{ ... }`는 함수를 호출했을 때 실행할 코드를 나타냅니다.

사실 첫 lesson부터 계속 썼던 `void SmallMain()`의 `void`도 정확히 같은 뜻입니다. `SmallMain`은 프로그램의 일을 실행하지만 결과값을 돌려주지는 않습니다.

조금 뒤에는 `void` 대신 `int`처럼 실제 값을 돌려주는 함수도 만들어 봅니다.

## 먼저 실행해 보세요

@code example1.cpp

## 입력을 받고 결과를 돌려주기
함수의 괄호 안에는 함수가 사용할 값을 받을 **parameter**를 적을 수 있습니다. `Square(int x)`를 호출할 때 `Square(5)`처럼 값을 주면 x가 그 값을 받습니다.

함수가 계산한 값을 돌려주려면 `return`을 사용합니다. `int Square(...)`의 앞쪽 `int`는 이 함수가 int 값을 돌려준다는 뜻입니다.

앞에서 본 `void PrintLine()`은 값을 돌려주지 않고, `int Square(int x)`는 int 값을 하나 돌려줍니다. 둘 다 함수이고, 앞의 return type이 함수가 어떤 결과를 돌려주는지 알려줍니다.

지금은 parameter를 **값으로 받는다**고 생각하면 충분합니다. Array처럼 큰 값을 전달할 때 실제 메모리에서 어떤 일이 일어나는지는 훨씬 뒤에서 자세히 살펴봅니다.

## 조금 바꾸어 보기

@code example2.cpp

## 함수는 작은 문제 하나를 맡게 하세요
좋은 함수 이름은 코드를 읽는 사람에게 **무슨 일을 하는지** 알려줍니다. 같은 계산이 여러 번 필요하거나, 여러 줄의 코드에 이름을 붙이면 이해하기 쉬워질 때 함수를 만들어 보세요.

처음부터 모든 코드를 함수로 나눌 필요는 없습니다. `SmallMain`에 간단히 쓰다가 반복되거나 의미 있는 한 덩어리가 보일 때 함수로 꺼내도 됩니다.



## 여러 줄을 주석으로 만들기

여러 줄에 걸쳐 메모를 남기고 싶다면 `/*`와 `*/` 사이를 주석으로 만들 수 있습니다. 예를 들어 `/* 이 부분은 점수에 보너스를 더하는 규칙을 설명합니다. */`처럼 사용할 수 있습니다.

보통 짧은 메모에는 `//`가 가장 편합니다. `/* ... */`는 여러 줄 설명이 정말 필요할 때 사용하면 됩니다.

좋은 주석은 `x = x + 1;`을 “x에 1을 더한다”라고 그대로 번역하기보다, **왜 이 코드가 필요한지** 또는 **이 코드 덩어리가 어떤 역할을 하는지** 알려줍니다.

## Exercise — 두 수의 합

두 int를 parameter로 받아 합을 돌려주는 `Add` 함수를 만들고, `SmallMain`에서 `Add(3, 7)`의 결과를 출력하세요.

@exercise exercise1_starter.cpp

### Hint

함수의 시작을 `int Add(int a, int b)`로 쓰고 `return a + b;`를 사용해 보세요.

@solution exercise1_solution.cpp

## Exercise — 가장 큰 수

int 세 개를 받아 가장 큰 값을 돌려주는 `Max3` 함수를 만드세요. `Max3(8, 3, 12)`를 출력해 확인하세요.

@exercise exercise2_starter.cpp

### Hint

먼저 `largest`에 a를 넣고, b와 c가 더 큰지 각각 if로 확인해 보세요.

@solution exercise2_solution.cpp

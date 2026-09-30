---
title: Repeating with while
part: basics
part-title: Part I — Programming Basics
goal: while을 이용해 조건이 참인 동안 반복합니다.
related-example: reference/console
---

## 몇 번 반복할지 미리 모를 때
`for`는 반복 횟수가 분명할 때 편했습니다. 하지만 사용자가 언제 0을 입력할지는 미리 알 수 없습니다. 이럴 때는 **조건이 참인 동안 계속하는** `while`을 사용할 수 있습니다.

아래 코드는 숫자가 5보다 작을 동안 반복합니다. 실행하기 전에 어떤 숫자가 나올지 예상해 보세요.

## 먼저 실행해 보세요

@code example1.cpp

## while은 조건을 먼저 확인합니다
`while (number <= 5)`는 반복을 시작하기 전에 조건을 검사합니다. true이면 `{`와 `}` 안을 실행하고 다시 조건으로 돌아갑니다. false가 되는 순간 반복을 끝냅니다.

따라서 반복 안에서 조건에 영향을 주는 값이 바뀌는지 확인하는 습관이 중요합니다. 다음 예제는 사용자가 0을 입력할 때까지 계속 숫자를 받습니다.

## 조금 바꾸어 보기

@code example2.cpp

## for와 while 중 무엇을 쓸까요?
`1부터 10까지`처럼 횟수가 분명하면 보통 `for`가 읽기 쉽습니다. `0을 입력할 때까지`, `게임 창이 열려 있는 동안`처럼 **언제 끝날지가 조건으로 정해진 경우**에는 `while`이 자연스럽습니다.

조건이 영원히 true이면 반복도 끝나지 않습니다. 실수로 무한 반복이 생기면 IDE의 **Stop**을 누르고, 반복 안에서 조건이 언젠가 false가 될 수 있는지 확인하세요.

## 매번 다른 값을 만들기
게임이나 간단한 simulation에서는 실행할 때마다 다른 값이 필요할 때가 많습니다. Small은 두 함수를 제공합니다.

`RandomInt(1, 6)`은 1부터 6까지의 정수 중 하나를 고릅니다. 양 끝인 1과 6도 포함됩니다.

`RandomReal(0.0, 1.0)`은 0.0 이상 1.0 미만의 real number를 만듭니다.

예를 들어 숫자 맞히기 게임의 정답은 `int secret = RandomInt(1, 100);`처럼 정할 수 있습니다. 자세한 사용법은 Examples의 **Random Numbers**와 **Number Guessing**에서 바로 실행해볼 수 있습니다.

## Exercise — 10부터 1까지

`while` 하나를 사용해 10부터 1까지 한 줄에 하나씩 출력하세요.

@exercise exercise1_starter.cpp

### Hint

`number`를 10으로 시작하고, `number >= 1`인 동안 출력한 뒤 1씩 줄여 보세요.

@solution exercise1_solution.cpp

## Exercise — 비밀번호 다시 묻기

정수 비밀번호를 입력받으세요. `1234`가 아니면 `Try again.`을 출력하고 다시 입력받습니다. `1234`를 입력하면 반복을 끝내고 `Welcome!`을 출력하세요.

@exercise exercise2_starter.cpp

### Hint

먼저 password를 한 번 입력받고 `while (password != 1234)` 안에서 다시 입력받아 보세요.

@solution exercise2_solution.cpp
